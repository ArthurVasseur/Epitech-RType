/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "Transform.hpp"

#include <memory>
#include <vector>

namespace Component
{
    struct Camera final
    {
        float m_boundX;
        float m_boundY;
    };
}
#endif /* !CAMERA_HPP_ */
