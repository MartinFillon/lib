/*
** EPITECH PROJECT, 2024
** lib
** File description:
** argsParser
*/

#ifndef ARGSPARSER_HPP_
#define ARGSPARSER_HPP_

#include <map>
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
            std::vector<std::string> getOtherArgs()
            {
                return _otherArgs;
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

#endif /* !ARGSPARSER_HPP_ */
