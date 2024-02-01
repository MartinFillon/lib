/*
** EPITECH PROJECT, 2024
** lib
** File description:
** argsParser
*/

#include "ArgsParser/ArgsParser.hpp"
#include <cstddef>
#include <string>
#include <vector>
#include "JsonParser/JsonParser.hpp"

namespace lib {

    Args::Parser::Parser(char **av, int ac, std::string confPath)
    {
        _conf = Json::Parser(confPath);
        _conf.parseJson();
        _av.reserve(ac);
        for (int i = 0; i < ac; i++)
            _av.push_back(av[i]);
    }

    void Args::Parser::parseArgs()
    {
        Json::JsonArray args = _conf.get<Json::JsonArray>("args");
        for (auto it = args.data.begin(); it != args.data.end(); it++) {
            Arg arg(std::get<Json::JsonObject>(*it));
            _args[arg.name] = arg;
        }

        for (size_t i = 0; i < _av.size(); i++) {
            if (parseShortArgs(&i))
                continue;
            if (parseLongArgs(&i))
                continue;
            _otherArgs.push_back(_av[i]);
        }
    }

    bool Args::Parser::parseShortArgs(size_t *index)
    {
        std::string arg = _av[*index];

        if (arg[0] != '-')
            return false;
        std::string name = arg.substr(1);

        for (auto it = _args.begin(); it != _args.end(); it++) {
            if (it->second.shortName == name) {
                it->second.found = true;
                if (it->second.hasValue) {
                    if (*index + 1 >= _av.size())
                        throw MissingArgException(
                            "Missing value for argument " + it->second.name
                        );
                    it->second.value = _av[*index + 1];
                }
                return true;
            }
        }
        return false;
    }

    bool Args::Parser::parseLongArgs(size_t *index)
    {
        std::string arg = _av[*index];

        if (arg[0] != '-' && arg[1] != '-')
            return false;
        std::string name = arg.substr(2);

        for (auto it = _args.begin(); it != _args.end(); it++) {
            if (it->second.name == name) {
                it->second.found = true;
                if (it->second.hasValue) {
                    if (name.find("=") == std::string::npos) {
                        if (*index + 1 >= _av.size())
                            throw MissingArgException(
                                "Missing value for argument " + it->second.name
                            );
                        it->second.value = _av[*index + 1];
                        *index += 1;
                    } else {
                        std::string value = name.substr(name.find("="));
                        value = value.substr(value.find("=") + 1);
                        it->second.value = value;
                    }
                }
                return true;
            }
        }
        return false;
    }

} // namespace lib
