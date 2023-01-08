/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** Lobby
*/

#ifndef LOBBY_HPP_
#define LOBBY_HPP_

#include "ISystem.hpp"
#include "Text.hpp"
#include "Registry.hpp"
#include "Physics.hpp"
#include "Render.hpp"
#include "Transform.hpp"
#include "World.hpp"

namespace System
{
    class Lobby : public ISystem
    {
    public:
        Lobby(Registry &r, World &world);
        ~Lobby();
        void update(float deltaTime, Registry &r);

        void stepUpdate(float deltaTime, Registry &r);

    protected:
    private:
    };
}
#endif /* !LOBBY_HPP_ */
