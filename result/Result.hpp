/*
** EPITECH PROJECT, 2024
** lib
** File description:
** Result
*/

#ifndef RESULT_HPP_
#define RESULT_HPP_

#include <stdexcept>

namespace lib {

    template <typename T, typename E>
    class Result {
      public:
        Result() = delete;

        Result(T *data) : _ok(data), _isOk(true) {}

        Result(E *err) : _err(err), _isOk(false) {}

        ~Result() = default;

        T unwrap() const
        {
            if (_isOk)
                return *_ok;
            throw *_err;
        }

        E unwrapErr() const
        {
            if (!_isOk)
                return *_err;
            else {
                throw std::runtime_error("Error: unknown error");
            }
        }

        T *unwrapMut()
        {
            if (_isOk)
                return _ok;
            throw *_err;
        }

        E *unwrapErrMut()
        {
            if (!_isOk)
                return _err;
            else {
                throw std::runtime_error("Error: unknown error");
            }
        }

        bool isOk() const
        {
            return _isOk;
        }

        bool isErr() const
        {
            return !_isOk;
        }

        bool operator==(const Result<T, E> &other) const
        {
            if (isOk() && other.isOk())
                return unwrap() == other.unwrap();
            if (isErr() && other.isErr())
                return unwrapErr() == other.unwrapErr();
            return false;
        }

        bool operator!=(const Result<T, E> &other) const
        {
            return !(*this == other);
        }

      protected:
        T *_ok = nullptr;
        bool _isOk = true;
        E *_err = nullptr;

      private:
    };
} // namespace lib

#endif /* !RESULT_HPP_ */
