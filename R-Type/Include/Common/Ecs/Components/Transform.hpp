/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** Transform
*/

#ifndef TRANSFOR_HPP_
#define TRANSFOR_HPP_

#include <iostream>
#include <iomanip>
#include "Vector2D.hpp"

namespace Component
{
    struct Transform
    {

        Transform(const Vector2Df &position, float rotation, const Vector2Df &scale) : _position(position), _rotation(rotation), _scale(scale) {}

        void translate(const Vector2Df &position)
        {
            translate(position.x, position.y);
        }

        void translate(float x, float y)
        {
            _position.x = _position.x + x;
            _position.y = _position.y + y;
        }

        Vector2Df _position;
        float _rotation;
        Vector2Df _scale;
    };
}

std::ostream &operator<<(std::ostream &os, const Component::Transform &transform);

#endif /* !TRANSFOR_HPP_ */
