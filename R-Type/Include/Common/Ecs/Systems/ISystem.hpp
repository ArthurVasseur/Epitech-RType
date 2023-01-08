/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** ISystem
*/

#ifndef ISYSTE_HPP_
#define ISYSTE_HPP_

#include <memory>
#include <vector>
#include "Registry.hpp"

namespace System
{
    class ISystem
    {
    public:
        virtual ~ISystem() = default;

        virtual void update(float deltaTime, Registry &r) = 0;

        virtual void stepUpdate(float deltaTime, Registry &r) = 0;
    };
}

#endif /* !ISYSTE_HPP_ */
