/*
** EPITECH PROJECT, 2024
** lib
** File description:
** jsonParser
*/

#include "JsonParser/JsonParser.hpp"

#include <cctype>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>

namespace lib {

    void Json::Parser::parseJson()
    {
        std::ifstream file(_path);
        std::stringstream buffer;

        if (!file.is_open()) {
            return;
        }

        buffer << file.rdbuf();
        _str = buffer.str();
        parseObject(nullptr, nullptr);
        file.close();
    }

    void Json::Parser::parseInner(Json::JsonObject *obj, Json::JsonArray *arr)
    {
        if (arr && obj)
            throw InvalidTokenException("Invalid token");
        if (getChar() == ':')
            _index++;
        skipSpaces();

        int c = getChar();
        if (c == '"')
            return parseString(obj, arr);
        if (c == '{')
            return parseObject(obj, arr);
        if (c == '[')
            return parseArray(obj, arr);
        if (c == 't' || c == 'f')
            return parseBool(obj, arr);
        if (c == '-' || std::isdigit(c))
            return parseNumber(obj, arr);
        throw InvalidTokenException(
            std::to_string((char)c) +
            " is an invalid token at index: " + std::to_string(_index)
        );
    }

    char Json::Parser::getChar()
    {
        if (_index >= _str.size()) {
            throw InvalidTokenException("Invalid token");
        }
        return _str[_index];
    }

    void Json::Parser::skipSpaces()
    {
        char c = getChar();

        while (c == ' ' || c == '\n' || c == '\t' || c == '\r') {
            _index++;
            c = getChar();
        }
    }

    static void escaped(std::string &s, char c)
    {
        switch (c) {
            case 'n':
                s += '\n';
                break;
            case 't':
                s += '\t';
                break;
            case 'r':
                s += '\r';
                break;
            default:
                s += c;
        }
    }

    void Json::Parser::parseString(Json::JsonObject *obj, Json::JsonArray *arr)
    {
        std::string value;
        if (getChar() == '"')
            _index++;
        while (getChar() != '"') {
            if (getChar() == '\\') {
                _index++;
                escaped(value, getChar());
            } else
                value += getChar();
            _index++;
        }
        _index++;
        Json::JsonValue jsonValue = value;
        appendValue(obj, arr, jsonValue);
    }

    void Json::Parser::parseObject(Json::JsonObject *obj, Json::JsonArray *arr)
    {
        Json::JsonObject n = Json::JsonObject();
        std::string key = _nextKey;

        skipSpaces();
        if (getChar() == '{')
            _index++;
        while (getChar() != '}') {
            skipSpaces();
            parseObjectInner(&n);
            skipSpaces();
        }
        _index++;
        Json::JsonValue tmp = n;
        if (!obj && !arr) {
            _jsonMap = n;
            return;
        }
        _nextKey = key;
        appendValue(obj, arr, tmp);
    }

    void Json::Parser::parseObjectInner(Json::JsonObject *obj)
    {
        switch (getChar()) {
            case '"':
                return parseKey();
            case ',':
                _index++;
                break;
            case ':':
                return parseInner(obj, nullptr);
            default:
                return;
        }
    }

    void Json::Parser::parseNumber(Json::JsonObject *obj, Json::JsonArray *arr)
    {
        int found_dot = 0;
        char *f;

        double num = strtod(_str.c_str() + _index, &f);

        if (getChar() == '-')
            _index++;
        while (std::isdigit(getChar()) || getChar() == '.') {
            found_dot += (getChar() == '.');
            _index++;
        }
        if (found_dot > 1 || getChar() == -1)
            throw InvalidTokenException("Number was malformed");
        JsonValue t(num);
        appendValue(obj, arr, t);
    }

    void Json::Parser::parseBool(Json::JsonObject *obj, Json::JsonArray *arr)
    {
        if (strncmp(_str.c_str() + _index, "true", 4) == 0) {
            JsonValue bl = true;
            getChar();
            appendValue(obj, arr, bl);
            _index += 4;
        } else if (strncmp(_str.c_str() + _index, "false", 4) == 0) {
            JsonValue bl = true;
            getChar();
            appendValue(obj, arr, bl);
            _index += 5;
        } else {
            throw InvalidTokenException(
                "Token is not true or false at index : " +
                std::to_string(_index)
            );
        }
    }

    void Json::Parser::parseArray(Json::JsonObject *obj, Json::JsonArray *arr)
    {
        JsonArray s;

        if (getChar() == '[')
            _index++;
        while (getChar() != ']') {
            skipSpaces();
            parseInner(nullptr, &s);
            skipSpaces();
            if (getChar() == ',')
                _index++;
        }
        _index++;
        JsonValue t(s);
        appendValue(obj, arr, t);
    }

    void Json::Parser::appendValue(
        Json::JsonObject *obj,
        Json::JsonArray *arr,
        Json::JsonValue &data
    )
    {
        if (obj)
            obj->data[_nextKey] = data;
        if (arr)
            arr->data.push_back(data);
    }

    void Json::Parser::parseKey()
    {
        _nextKey.clear();
        _index++;

        while (getChar() != '"') {
            _nextKey += getChar();
            _index++;
        }
        _index++;
    }

    bool Json::JsonObject::operator==(const JsonObject &rhs) const
    {
        return data == rhs.data;
    }

    bool Json::JsonObject::operator!=(const JsonObject &rhs) const
    {
        return !(rhs == *this);
    }

    bool Json::JsonArray::operator==(const JsonArray &rhs) const
    {
        return data == rhs.data;
    }

    bool Json::JsonArray::operator!=(const JsonArray &rhs) const
    {
        return !(rhs == *this);
    }
} // namespace lib

std::ostream &operator<<(std::ostream &os, const lib::Json::JsonValue &v)
{
    std::visit(
        [&os](auto &&arg) {
            if constexpr (std::is_same_v<
                              std::decay_t<decltype(arg)>,
                              std::string>)
                os << "\"" << arg << "\"";
            else
                os << std::boolalpha << arg;
        },
        v
    );
    return os;
}

std::ostream &operator<<(std::ostream &os, const lib::Json::JsonObject &obj)
{
    os << '{';
    for (auto it = obj.data.begin(); it != obj.data.end(); it++) {
        os << "\"" << it->first << "\": " << it->second;
        if (std::next(it) != obj.data.end())
            os << ',' << std::endl;
    }
    os << '}';
    return os;
}

std::ostream &operator<<(std::ostream &os, const lib::Json::JsonArray &obj)
{
    os << '[';
    for (auto it = obj.data.begin(); it != obj.data.end(); it++) {
        os << *it;
        if (std::next(it) != obj.data.end())
            os << ',' << std::endl;
    }
    os << ']';
    return os;
}
