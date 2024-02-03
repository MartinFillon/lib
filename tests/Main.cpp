/*
** EPITECH PROJECT, 2024
** pipunit
** File description:
** main
*/

#include <vector>
#include "pipunit/include/Test.hpp"

std::vector<pipunit::Test> JsonParserSpec();
std::vector<pipunit::Test> EitherSpec();

int main(void)
{
    std::vector<pipunit::Test> suite = JsonParserSpec();
    std::vector<pipunit::Test> eitherSuite = EitherSpec();

    for (auto &test : eitherSuite) {
        suite.push_back(test);
    }

    if (!pipunit::printResult(suite)) {
        pipunit::printTests(suite);
        return 1;
    }
    return 0;
}
