/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** Physics
*/

#ifndef ENEMY_HPP_
#define ENEMY_HPP_

#include "Vector2D.hpp"
#include "Registry.hpp"
#include "ISystem.hpp"

namespace System
{
    class Enemy : public ISystem
    {
    public:
        Enemy() = default;

        ~Enemy() = default;

        void update(float deltatime, Registry &r);
        void stepUpdate(float deltatime, Registry &r);

    protected:
    private:
    };
}

#endif /* !ENEMY_HPP_ */