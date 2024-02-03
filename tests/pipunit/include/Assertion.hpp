/*
** EPITECH PROJECT, 2024
** pipunit
** File description:
** Assertion
*/

#ifndef ASSERTION_HPP_
#define ASSERTION_HPP_

#include <sstream>
#include <string>

namespace pipunit {

    class Assertion {
      public:
        Assertion(){};
        Assertion(bool result, std::string assertion)
            : _result(result), _assert(assertion){};
        ~Assertion(){};

        bool getResult()
        {
            return _result;
        };

        std::string prettyString()
        {
            std::string res = _assert;
            res += " : ";
            res += _result ? "OK" : "KO";
            return res;
        };

        Assertion operator&&(const Assertion &a)
        {
            return Assertion(
                _result && a._result, (_assert + " && " + a._assert)
            );
        }

      protected:
        bool _result = false;
        std::string _assert;

      private:
    };

    template <typename T> std::string to_string(const T &obj)
    {
        std::stringstream ss;
        ss << obj;
        return ss.str();
    }

    template <typename T> Assertion assert_equals(T a, T b)
    {
        return Assertion(a == b, to_string(a) + " == " + to_string(b));
    }

    template <typename T> Assertion assert_not_equals(T a, T b)
    {
        return Assertion(a != b, to_string(a) + " != " + to_string(b));
    }

    template <typename T> Assertion assert_greater(T a, T b)
    {
        return Assertion(a > b, to_string(a) + " > " + to_string(b));
    }

    template <typename T> Assertion assert_less(T a, T b)
    {
        return Assertion(a < b, to_string(a) + " < " + to_string(b));
    }

    template <typename T> Assertion assert_greater_equals(T a, T b)
    {
        return Assertion(a >= b, to_string(a) + " >= " + to_string(b));
    }

    template <typename T> Assertion assert_less_equals(T a, T b)
    {
        return Assertion(
            a <= b, std::to_string(a) + " <= " + std::to_string(b)
        );
    }

    template <typename T> Assertion assert_true(T a)
    {
        return Assertion(a, std::to_string(a) + " == true");
    }

    template <typename T> Assertion assert_false(T a)
    {
        return Assertion(!a, std::to_string(a) + " == false");
    }

} // namespace pipunit
#endif /* !ASSERTION_HPP_ */
