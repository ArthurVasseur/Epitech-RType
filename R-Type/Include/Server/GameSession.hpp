/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** GameSession
*/

#ifndef GAMESESSION_HPP_
#define GAMESESSION_HPP_
#include <chrono>
#include "Registry.hpp"
#include "World.hpp"
#include "NetCode.hpp"
#include "Transform.hpp"
#include "Ship.hpp"
#include "Replication.hpp"
#include "Shot.hpp"
#include "Collisions.hpp"
#include "Spawner.hpp"
#include "Enemy.hpp"
class GameSession
{
public:
    GameSession(short port) : _world(_registry, [this, port](Registry &r)
                                     {
                                         _world.addSystem<System::NetCode>(port);
                                         _world.addSystem<System::Collisions>();
                                         _world.addSystem<System::Shot>();
                                         _world.addSystem<System::Spawner>(r);
                                         _world.addSystem<System::Enemy>();
                                     })
    {
    }
    void run()
    {
        std::chrono::time_point<std::chrono::high_resolution_clock> lastFrameTime = std::chrono::high_resolution_clock::now();
        float deltaTime = 0.f;
        float timeStep = 0.02f;
        float timeUpdate = 0.01f;
        float stepUpdateremainingTime = 0.f;
        float updateremainingTime = 0.f;

        while (true)
        {
            auto beginTime = std::chrono::high_resolution_clock::now();
            deltaTime = std::chrono::duration<float>(beginTime - lastFrameTime).count();
            lastFrameTime = beginTime;
            stepUpdateremainingTime += deltaTime;
            updateremainingTime += deltaTime;

            while (updateremainingTime >= timeUpdate)
            {
                _world.update(updateremainingTime);
                updateremainingTime -= timeUpdate;
            }

            while (stepUpdateremainingTime >= timeStep)
            {
                _world.stepUpdate(timeStep);
                stepUpdateremainingTime -= timeStep;
            }
        }
    };
    ~GameSession() = default;

protected:
private:
    Registry _registry;
    World _world;
};

#endif /* !GAMESESSION_HPP_ */
