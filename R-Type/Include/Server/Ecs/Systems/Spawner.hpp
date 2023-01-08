/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** Physics
*/

#ifndef SPAWNER_HPP_
#define SPAWNER_HPP_

#include "Vector2D.hpp"
#include "Registry.hpp"
#include "ISystem.hpp"

namespace System
{
    class Spawner : public ISystem
    {
    public:
        Spawner(Registry &r);

        ~Spawner() = default;

        void update(float deltatime, Registry &r);
        void stepUpdate(float deltatime, Registry &r);

    protected:
    private:
    };
}

#endif /* !SPAWNER_HPP_ */