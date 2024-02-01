/*
** EPITECH PROJECT, 2024
** pipunit
** File description:
** Test
*/

#ifndef TEST_HPP_
#define TEST_HPP_

#include <iostream>
#include <string>
#include <vector>

#include "Redirect.hpp"

namespace pipunit {

    class Test {
      public:
        Test(
            std::string name,
            std::string desc,
            Assertion (*f)(CoutRedirect *, CerrRedirect *) = NULL,
            CoutRedirect *(*cout_redirect)() = NULL,
            CerrRedirect *(*cerr_redirect)() = NULL
        )
            : _name(name), _desc(desc)
        {
            CoutRedirect *cout = NULL;
            CerrRedirect *cerr = NULL;
            if (cout_redirect != NULL)
                cout = cout_redirect();
            if (cerr_redirect != NULL)
                cerr = cerr_redirect();
            if (f)
                _result = f(cout, cerr);
            else
                _result = Assertion(false, "No test function");
            if (cout)
                delete cout;
            if (cerr)
                delete cerr;
        }

        ~Test() {}

        bool getResult()
        {
            return _result.getResult();
        };

        void prettyPrint()
        {
            std::cout << _name << ": " << _desc << ": "
                      << _result.prettyString() << std::endl;
        }

      protected:
        std::string _name;
        std::string _desc;
        Assertion _result = Assertion();

      private:
    };

    void printTests(std::vector<Test>);
    bool printResult(std::vector<Test>);
} // namespace pipunit

#endif /* !TEST_HPP_ */
