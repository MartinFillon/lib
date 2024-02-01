/*
** EPITECH PROJECT, 2024
** pipunit
** File description:
** Test
*/

#include "Test.hpp"
#include <vector>

namespace pipunit {

    void printTests(std::vector<Test> tests)
    {
        for (auto test : tests) {
            test.prettyPrint();
        }
    }

    bool printResult(std::vector<Test> tests)
    {
        int passed = 0;
        int failed = 0;
        for (auto test : tests) {
            if (test.getResult())
                passed++;
            else
                failed++;
        }
        std::cout << "\033[1;34mPipunit\033[0m" << std::endl;
        std::cout << "Total"
                  << ": " << tests.size() << std::endl;
        std::cout << "\033[1;32mPassed: " << passed << "\033[0m" << std::endl;
        std::cout << "\033[1;31mFailed: " << failed << "\033[0m" << std::endl;
        return failed == 0;
    }

} // namespace pipunit
