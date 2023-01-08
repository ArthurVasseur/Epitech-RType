/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** Collision
*/

#ifndef COLLISIONS_HPP_
#define COLLISIONS_HPP_

#include "Vector2D.hpp"
#include "Registry.hpp"
#include "ISystem.hpp"

namespace System
{
    class Collisions : public ISystem
    {
    public:
        Collisions() = default;

        ~Collisions() = default;

        void update(float deltatime, Registry &r);
        void stepUpdate(float deltatime, Registry &r);

    protected:
    private:
    };
}

#endif /* !COLLISIONS_HPP_ */