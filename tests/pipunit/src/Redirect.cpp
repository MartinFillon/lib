/*
** EPITECH PROJECT, 2024
** pipunit
** File description:
** Redirect
*/

#include "Redirect.hpp"
#include "Assertion.hpp"

namespace pipunit {

CoutRedirect *redirectStdout()
{
    return new CoutRedirect();
}

CerrRedirect *redirectStderr()
{
    return new CerrRedirect();
}

CoutRedirect::CoutRedirect()
{
    old = std::cout.rdbuf(buffer.rdbuf());
}

std::string CoutRedirect::getString()
{
    return buffer.str();
}

CoutRedirect::~CoutRedirect()
{
    std::cout.rdbuf(old);
}

CerrRedirect::CerrRedirect()
{
    old = std::cerr.rdbuf(buffer.rdbuf());
}

std::string CerrRedirect::getString()
{
    return buffer.str();
}

CerrRedirect::~CerrRedirect()
{
    std::cerr.rdbuf(old);
}

Assertion assert_stdout_equals(CoutRedirect *cout, std::string str)
{
    return Assertion(cout->getString() == str, "stdout == " + str);
}

Assertion assert_stderr_equals(CerrRedirect *cerr, std::string str)
{
    return Assertion(cerr->getString() == str, "stderr == " + str);
}

Assertion assert_stdout_contains(CoutRedirect *cout, std::string str)
{
    return Assertion(
        cout->getString().find(str) != std::string::npos,
        "stdout contains " + str
    );
}

Assertion assert_stderr_contains(CerrRedirect *cerr, std::string str)
{
    return Assertion(
        cerr->getString().find(str) != std::string::npos,
        "stderr contains " + str
    );
}

Assertion assert_stdout_not_contains(CoutRedirect *cout, std::string str)
{
    return Assertion(
        cout->getString().find(str) == std::string::npos,
        "stdout not contains " + str
    );
}

Assertion assert_stderr_not_contains(CerrRedirect *cerr, std::string str)
{
    return Assertion(
        cerr->getString().find(str) == std::string::npos,
        "stderr not contains " + str
    );
}

} // namespace pipunit
