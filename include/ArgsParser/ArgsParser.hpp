/*
** EPITECH PROJECT, 2024
** lib
** File description:
** argsParser
*/

#ifndef ARGSPARSER_HPP_
#define ARGSPARSER_HPP_

#include <ios>
#include <iostream>
#include <map>
#include <ostream>
#include <string>
#include <vector>

#include "JsonParser/JsonParser.hpp"

namespace lib {

    namespace Args {

        class MissingArgException : public std::exception {
          public:
            MissingArgException(std::string const &message) throw()
                : _message(message)
            {
            }

            ~MissingArgException() throw() {}

            const char *what() const throw()
            {
                return _message.c_str();
            }

          private:
            std::string _message;
        };

        class Arg {
          public:
            Arg() = default;

            Arg(Json::JsonObject _conf)
            {
                std::cout << _conf << std::endl;
                name = _conf.get<std::string>("name");
                description = _conf.get<std::string>("description");
                required = _conf.get<bool>("required");
                hasValue = _conf.get<bool>("hasValue");
                shortName = _conf.get<std::string>("Short");
                value = "";
                found = false;
            }

            ~Arg() = default;

            std::string name;
            std::string shortName;
            std::string description;
            bool required;
            bool hasValue;
            std::string value;
            bool found;
        };

        class Parser {
          public:
            Parser() = delete;

            Parser(char **av, int ac, std::string confPath);

            ~Parser() = default;
            /**
            ** @brief Parse the arguments
            ** @return void
            */
            void parseArgs();

            /**
            ** @brief Get the value of an argument
            ** @param name The name of the arg
            ** @return The value of the arg
            */
            std::string getArg(std::string name)
            {
                return _args[name].value;
            }

            /**
            ** @brief Check if an argument has been found
            ** @param name The name of the arg
            ** @return true if the arg has been found, false otherwise
            */
            bool hasArg(std::string name)
            {
                return _args[name].found;
            }

            /**
            ** @brief Get the other arguments
            ** @return The other arguments
            */
            const std::vector<std::string> getOtherArgs() const
            {
                return _otherArgs;
            }

            const std::map<std::string, Arg> &getArgs() const
            {
                return _args;
            }

          protected:
            std::vector<std::string> _av;
            std::map<std::string, Arg> _args;
            std::vector<std::string> _otherArgs;
            Json::Parser _conf;

          private:
            bool parseShortArgs(size_t *index);
            bool parseLongArgs(size_t *index);
        };
    } // namespace Args
} // namespace lib

inline std::ostream &operator<<(std::ostream &os, const lib::Args::Arg &arg)
{
    os << arg.name << ": " << std::endl;
    os << "long: "
       << "--" << arg.name << std::endl;
    os << "short: "
       << "-" << arg.shortName << std::endl;
    os << "description: " << arg.description << std::endl;
    os << std::boolalpha << "required: " << arg.required << std::endl;
    os << "hasValue: " << arg.hasValue << std::endl;
    os << "value: " << arg.value << std::endl;
    return os;
}

inline std::ostream &operator<<(
    std::ostream &os,
    const lib::Args::Parser &parser
)
{
    os << "Args: " << std::endl;
    const auto &args = parser.getArgs();
    for (auto it = args.begin(); it != args.end(); it++) {
        os << it->second << std::endl;
    }
    os << "Other args: " << std::endl;
    const auto &otherArgs = parser.getOtherArgs();
    for (auto it = otherArgs.begin(); it != otherArgs.end(); it++) {
        os << *it << std::endl;
    }
    return os;
}

#endif /* !ARGSPARSER_HPP_ */
