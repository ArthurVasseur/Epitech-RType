/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** Physics
*/

#ifndef SHOT_HPP_
#define SHOT_HPP_

#include "Vector2D.hpp"
#include "Registry.hpp"
#include "ISystem.hpp"

namespace System
{
    class Shot : public ISystem
    {
    public:
        Shot() = default;

        ~Shot() = default;

        void update(float deltatime, Registry &r);
        void stepUpdate(float deltatime, Registry &r);

    protected:
    private:
    };
}

#endif /* !SHOT_HPP_ */