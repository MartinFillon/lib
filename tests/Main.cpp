/*
** EPITECH PROJECT, 2024
** pipunit
** File description:
** main
*/

#include <vector>
#include "pipunit/include/Test.hpp"

std::vector<pipunit::Test> JsonParserSpec();

int main(void)
{
    std::vector<pipunit::Test> suite = JsonParserSpec();
    if (!pipunit::printResult(suite)) {
        pipunit::printTests(suite);
        return 1;
    }
    return 0;
}
