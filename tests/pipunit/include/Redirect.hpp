/*
** EPITECH PROJECT, 2024
** pipunit
** File description:
** Redirect
*/

#include <iostream>
#include <sstream>
#include <streambuf>
#include <string>
#include "Assertion.hpp"

namespace pipunit {
    class CoutRedirect {

      public:
        CoutRedirect();
        std::string getString();
        ~CoutRedirect();

      private:
        std::stringstream buffer;
        std::streambuf *old;
    };

    class CerrRedirect {

      public:
        CerrRedirect();
        std::string getString();
        ~CerrRedirect();

      private:
        std::stringstream buffer;
        std::streambuf *old;
    };

    CoutRedirect *redirectStdout();
    CerrRedirect *redirectStderr();

    Assertion assert_stdout_equals(CoutRedirect *cout, std::string str);
    Assertion assert_stderr_equals(CerrRedirect *cerr, std::string str);
    Assertion assert_stdout_not_equals(CoutRedirect *cout, std::string str);
    Assertion assert_stderr_not_equals(CerrRedirect *cerr, std::string str);
    Assertion assert_stdout_contains(CoutRedirect *cout, std::string str);
    Assertion assert_stderr_contains(CerrRedirect *cerr, std::string str);
    Assertion assert_stdout_not_contains(CoutRedirect *cout, std::string str);
    Assertion assert_stderr_not_contains(CerrRedirect *cerr, std::string str);

} // namespace pipunit
