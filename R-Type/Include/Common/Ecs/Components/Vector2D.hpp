/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** Vector2D
*/

#ifndef VECTOR2D_HPP_
#define VECTOR2D_HPP_
#include <iostream>
#include <type_traits>

namespace Component
{

    template <class T>
    struct Vector2D
    {
        Vector2D(const T x, const T y) : x(x), y(y) {}
        ~Vector2D() = default;
        T x;
        T y;

        Vector2D<T> operator+(const Vector2D<T> &right)
        {
            return Vector2D<T>(x + right.x, y + right.y);
        }

        Vector2D<T> operator-(const Vector2D<T> &right)
        {
            return Vector2D<T>(x - right.x, y - right.y);
        }

        Vector2D<T> &operator+=(const Vector2D<T> &right)
        {
            x += right.x;
            y += right.y;

            return (*this);
        }

        Vector2D<T> &operator-=(const Vector2D<T> &right)
        {
            x -= right.x;
            y -= right.y;

            return (*this);
        }

        Vector2D<T> operator*(const Vector2D<T> &right)
        {
            return Vector2D<T>(x * right.x, y * right.y);
        }

        template <typename T2>
        Vector2D<T> operator*(const T2 value)
        {
            static_assert(std::is_arithmetic<T2>::value, "T is not arithmetic");
            x *= value;
            y *= value;
            return (*this);
        }

        Vector2D<T> &operator*=(const Vector2D<T> &right)
        {
            x *= right;
            y *= right;

            return (*this);
        }

        Vector2D<T> operator/(const Vector2D<T> right)
        {
            return Vector2D<T>(x / right, y / right);
        }

        Vector2D<T> operator/(const T val)
        {
            static_assert(std::is_arithmetic<T>::value, "T is not arithmetic");
            return Vector2D<T>(x / val, y / val);
        }

        Vector2D<T> &operator/=(const Vector2D<T> right)
        {
            x /= right;
            y /= right;

            return (*this);
        }

        bool operator==(const Vector2D<T> &right)
        {
            return (x == right.x) && (y == right.y);
        }

        bool operator!=(const Vector2D<T> &right)
        {
            return (x != right.x) || (y != right.y);
        }
    };

    using Vector2Df = Vector2D<float>;
    using Vector2Dd = Vector2D<double>;
    using Vector2Di = Vector2D<int>;
    template <typename T>
    Vector2D<T> operator+(T val, const Vector2D<T> &vec)
    {
        return Vector2D<T>(vec.x + val, vec.y + val);
    }

    template <typename T>
    Vector2D<T> operator+(const Vector2D<T> &vec, T value)
    {
        return Vector2D<T>(vec.x + value, vec.y + value);
    }

    template <typename T>
    Vector2D<T> operator+(const Vector2D<T> &vec, const Vector2D<T> &vec1)
    {
        return Vector2D<T>(vec.x + vec1.x, vec.y + vec1.y);
    }

    template <typename T>
    Vector2D<T> operator*(T val, const Vector2D<T> &vec)
    {
        return Vector2D<T>(vec.x * val, vec.y * val);
    }

    template <typename T>
    Vector2D<T> operator*(const Vector2D<T> &vec, T value)
    {
        return Vector2D<T>(vec.x * value, vec.y * value);
    }
}

template <class T>
std::ostream &operator<<(std::ostream &os, const Component::Vector2D<T> &vector)
{
    os << "Vector2D" << std::endl;
    os << "\t( " << vector.x << ", " << vector.y << " )" << std::endl;
    return (os);
}

#endif /* !VECTOR2D_HPP_ */
