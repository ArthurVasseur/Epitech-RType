/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** main
*/
#include <chrono>
#include "Registry.hpp"
#include "World.hpp"
#include "Physics.hpp"
#include "Render.hpp"
#include "Transform.hpp"
#include "Sprite.hpp"
#include "Background.hpp"
#include "Lobby.hpp"
#include "Rectangle.hpp"
#include "Tag.hpp"
#include "Net.hpp"
#include "TextBox.hpp"

#include "Audio.hpp"

int main(int argc, const char *argv[])
{
    if (argc != 2)
        return 84;
    std::string ip = std::string(argv[1]);
    Registry registry;
    std::shared_ptr<EventHandler> handler = std::make_shared<EventHandler>();
    World world(registry, [](Registry &r) {

    });
        auto &render = world.addSystem<System::Render>(handler);
        auto entity = registry.addEntity();
        auto &background = world.addSystem<System::Background>(registry);
        auto &audio = world.addSystem<System::Audio>();
        auto playerEntity = registry.addEntity();
        auto audioEntity = registry.addEntity();
        world.addSystem<System::Net>(handler, registry, ip, 2121, world);
        registry.emplaceComponent<Component::AudioSource>(audioEntity, Component::AudioSource("./assets/music/1.ogg", true, true, Component::AudioSource::MUSIC));

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
            world.update(updateremainingTime);
            updateremainingTime -= timeUpdate;
        }

        while (stepUpdateremainingTime >= timeStep)
        {
            world.stepUpdate(timeStep);
            stepUpdateremainingTime -= timeStep;
        }
    }

    return 0;
}
