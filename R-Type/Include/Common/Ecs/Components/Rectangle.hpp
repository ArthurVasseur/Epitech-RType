/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** Rectangle
*/

#ifndef RECTANGLE_HPP_
#define RECTANGLE_HPP_

#include "Vector2D.hpp"

namespace Component
{
    struct Rectangle
    {
        explicit Rectangle(const Vector2Df &size) : _size(size) {}
        Rectangle(float w, float h) : _size(Vector2Df(w, h)) {}
        Vector2Df _size;
    };
}

#endif /* !RECTANGLE_HPP_ */
