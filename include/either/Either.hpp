/*
** EPITECH PROJECT, 2024
** lib
** File description:
** Either
*/

#ifndef EITHER_HPP_
#define EITHER_HPP_

#include <exception>
#include <functional>
#include <string>

namespace lib {

    template <typename L, typename R>
    class Either {
      public:
        class EitherException : public std::exception {
          public:
            explicit EitherException(const std::string &message)
                : _message(message)
            {
            }

            ~EitherException() override = default;

            const char *what() const noexcept override
            {
                return _message.c_str();
            }

          private:
            std::string _message;
        };

        Either() = delete;
        ~Either() = default;

        Either(L *left) : _left(left), _isLeft(true) {}

        Either(R *right) : _right(right), _isLeft(false) {}

        /**
        ** @brief Unwrap the left value
        **      Throws an exception if the Either is not left
        ** @return The left value
        **/
        L unwrapLeft() const
        {
            if (_isLeft)
                return *_left;
            else {
                throw EitherException("Either is not left");
            }
        }

        /**
        ** @brief Unwrap the right value
        **      Throws an exception if the Either is not right
        ** @return The right value
        **/
        R unwrapRight() const
        {
            if (!_isLeft)
                return *_right;
            else {
                throw EitherException("Either is not right");
            }
        }

        /**
        ** @brief Unwrap the left value
        **      Throws an exception if the Either is not left
        ** @return The left value
        **/
        L *unwrapMutLeft()
        {
            if (_isLeft)
                return _left;
            else {
                throw EitherException("Either is not left");
            }
        }

        /**
        ** @brief Unwrap the right value
        **      Throws an exception if the Either is not right
        ** @return The right value
        **/
        R *unwrapMutRight()
        {
            if (!_isLeft)
                return _right;
            else {
                throw EitherException("Either is not right");
            }
        }

        /**
        ** @brief Check if the Either is left
        ** @return True if the Either is left, false otherwise
        **/
        bool isLeft() const
        {
            return _isLeft;
        }

        /**
        ** @brief Check if the Either is right
        ** @return True if the Either is right, false otherwise
        **/
        bool isRight() const
        {
            return !_isLeft;
        }

        /**
        ** @brief Map the Either
        ** @param f The function to apply
        **/
        void map(std::function<void(L *, R *)> f)
        {
            if (_isLeft)
                f(_left, nullptr);
            else
                f(nullptr, _right);
        }

        bool operator==(const Either<L, R> &other) const
        {
            if (isLeft() && other.isLeft())
                return unwrapLeft() == other.unwrapLeft();
            if (isRight() && other.isRight())
                return unwrapRight() == other.unwrapRight();
            return false;
        }

        bool operator!=(const Either<L, R> &other) const
        {
            return !(*this == other);
        }

      protected:
        L *_left = nullptr;
        bool _isLeft = true;
        R *_right = nullptr;

      private:
    };

} // namespace lib

#endif /* !EITHER_HPP_ */
