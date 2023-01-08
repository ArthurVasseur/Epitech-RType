/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** Physics
*/

#ifndef PHYSICS_HPP_
#define PHYSICS_HPP_

#include "Vector2D.hpp"
#include "Registry.hpp"
#include "ISystem.hpp"

namespace System
{
    class Physics : public ISystem
    {
    public:
        Physics() = default;

        ~Physics() = default;

        void update(float deltatime, Registry &r);
        void stepUpdate(float deltatime, Registry &r);

    protected:
    private:
        const Component::Vector2Df _gravity = Component::Vector2Df(0.0f, -9.80665f);
        const float _friction = 0.95f;
    };
}

#endif /* !PHYSICS_HPP_ */
