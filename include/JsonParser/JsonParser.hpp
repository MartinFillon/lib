/*
** EPITECH PROJECT, 2024
** lib
** File description:
** jsonParser
*/

#ifndef JSONPARSER_HPP_
#define JSONPARSER_HPP_

#include <cstddef>
#include <ostream>
#include <string>
#include <variant>
#include <vector>
#include <unordered_map>

namespace lib {
    namespace Json {

        class InvalidTokenException : public std::exception {
          public:
            InvalidTokenException(const std::string &token) : _token(token) {}

            InvalidTokenException(const char &token)
            {
                std::string str;
                str.push_back(token);

                _token = str;
            }

            ~InvalidTokenException() = default;

            const char *what() const noexcept override
            {
                return _token.c_str();
            }

          private:
            std::string _token;
        };

        class JsonObject;
        class JsonArray;

        typedef std::variant<std::string, double, bool, JsonObject, JsonArray>
            JsonValue;

        class JsonObject {
          public:
            JsonObject() = default;
            ~JsonObject() = default;

            template <typename T>
            T get(const std::string &key)
            {
                return std::get<T>(data[key]);
            }

            std::unordered_map<std::string, JsonValue> data;

            bool operator==(const JsonObject &other) const;
            bool operator!=(const JsonObject &other) const;
        };

        class JsonArray {
          public:
            JsonArray() = default;
            ~JsonArray() = default;

            JsonValue &operator[](size_t idx)
            {
                return data[idx];
            }

            std::vector<JsonValue> data;
            bool operator==(const JsonArray &other) const;
            bool operator!=(const JsonArray &other) const;
        };

        class Parser {
          public:
            Parser(const std::string &path) : _path(path) {}

            Parser() = default;

            ~Parser() = default;

            void parseJson();

            /**
            ** @brief Get the value of a key in the json
            ** @param key The key to get the value of
            ** @return The value of the key
            */
            template <typename T>
            T get(const std::string &key)
            {
                return _jsonMap.get<T>(key);
            }

            /**
            ** @brief Get the json
            ** @return The json as an object seperated from the parser
            */
            JsonObject &getJson()
            {
                return _jsonMap;
            }

            /**
            ** @brief Get the json as const
            ** @return The json as an object seperated from the parser
            */
            const JsonObject &getJson() const
            {
                return _jsonMap;
            }

          protected:
            std::string _path;
            std::string _str;
            size_t _index = 0;

            std::string _nextKey;
            JsonObject _jsonMap;

          private:
            void parseInner(JsonObject *, JsonArray *);
            char getChar();
            void skipSpaces();
            void parseString(JsonObject *, JsonArray *);
            void parseObject(JsonObject *, JsonArray *);
            void parseNumber(JsonObject *, JsonArray *);
            void parseBool(JsonObject *, JsonArray *);
            void parseArray(JsonObject *, JsonArray *);
            void
            appendValue(Json::JsonObject *, Json::JsonArray *, Json::JsonValue &);
            void parseObjectInner(Json::JsonObject *);
            void parseKey();
        };
    } // namespace Json
} // namespace lib

std::ostream &operator<<(std::ostream &, const lib::Json::JsonValue &);
std::ostream &operator<<(std::ostream &, const lib::Json::JsonObject &);
std::ostream &operator<<(std::ostream &, const lib::Json::JsonArray &);
#endif /* !JSONPARSER_HPP_ */
