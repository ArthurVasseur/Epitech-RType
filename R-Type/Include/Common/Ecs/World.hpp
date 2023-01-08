/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** World
*/

#ifndef WORLD_HPP_
#define WORLD_HPP_

#include <vector>
#include <memory>
#include <type_traits>
#include <exception>
#include <functional>
#include "Registry.hpp"
#include "ISystem.hpp"

class World
{
public:
    World(Registry &r, std::function<void(Registry &r)> onContruct) : _registry(r)
    {
        onContruct(r);
    }

    ~World() = default;

    template <typename T, typename... Args>
    T &addSystem(Args &&...args)
    {
        _systems.push_back(std::make_unique<T>(std::forward<Args>(args)...));
        return (static_cast<T &>(*_systems.back()));
    }

    Entity addEntity()
    {
        return _registry.addEntity();
    }

    void update(float deltaTime)
    {
        for (auto &system : _systems)
        {
            try
            {
                system->update(deltaTime, _registry);
            }
            catch (const std::exception &e)
            {
            }
        }
    }

    void stepUpdate(float deltaTime)
    {
        try
        {
            for (auto &system : _systems)
                system->stepUpdate(deltaTime, _registry);
        }
        catch (...)
        {
        }
    }

private:
    std::vector<std::unique_ptr<System::ISystem>> _systems;
    Registry &_registry;
};

#endif /* !WORLD_HPP_ */
