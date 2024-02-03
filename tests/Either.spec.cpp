/*
** EPITECH PROJECT, 2024
** lib
** File description:
** Either.spec
*/

#include <vector>

#include "Either/Either.hpp"
#include "pipunit/include/Assertion.hpp"
#include "pipunit/include/Test.hpp"

pipunit::Assertion assert_either_left(
    pipunit::CoutRedirect *cout,
    pipunit::CerrRedirect *cerr
)
{
    (void)cout;
    (void)cerr;

    int value = 42;

    lib::Either<int, std::string> either =
        lib::Either<int, std::string>(&value);
    return pipunit::assert_true(either.isLeft());
}

pipunit::Assertion assert_either_right(
    pipunit::CoutRedirect *cout,
    pipunit::CerrRedirect *cerr
)
{
    (void)cout;
    (void)cerr;

    std::string value = "42";

    lib::Either<int, std::string> either =
        lib::Either<int, std::string>(&value);
    return pipunit::assert_true(either.isRight());
}

std::vector<pipunit::Test> EitherSpec()
{
    std::vector<pipunit::Test> tests;

    tests.push_back(pipunit::Test{
        "assert_either_left",
        "test if either is left",
        &assert_either_left,
        nullptr,
        nullptr
    });

    tests.push_back(pipunit::Test{
        "assert_either_right",
        "test if either is right",
        &assert_either_right,
        nullptr,
        nullptr
    });
    return tests;
}
