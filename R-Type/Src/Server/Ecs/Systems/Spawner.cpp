/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** Spawner
*/

#include "Spawner.hpp"
#include "Transform.hpp"
#include "Tag.hpp"
#include "Ship.hpp"
#include "Replication.hpp"
#include "Collider.hpp"

namespace System
{
    Spawner::Spawner(Registry &r) {
        auto spawnerA = r.addEntity();
        auto spawnerB = r.addEntity();
        auto spawnerD = r.addEntity();
        auto spawnerE = r.addEntity();
        auto spawnerG = r.addEntity();
        r.emplaceComponent<Component::Tag>(spawnerA, Component::Tag("spawner"));
        r.emplaceComponent<Component::Tag>(spawnerB, Component::Tag("spawner"));
        r.emplaceComponent<Component::Tag>(spawnerD, Component::Tag("spawner"));
        r.emplaceComponent<Component::Tag>(spawnerE, Component::Tag("spawner"));
        r.emplaceComponent<Component::Tag>(spawnerG, Component::Tag("spawner"));
        r.emplaceComponent<Component::Transform>(spawnerA, Component::Transform(Component::Vector2Df(2400, 500), 0, Component::Vector2Df(1,1)));
        r.emplaceComponent<Component::Transform>(spawnerB, Component::Transform(Component::Vector2Df(3500, 200), 0, Component::Vector2Df(1,1)));
        r.emplaceComponent<Component::Transform>(spawnerD, Component::Transform(Component::Vector2Df(5000, 600), 0, Component::Vector2Df(1,1)));
        r.emplaceComponent<Component::Transform>(spawnerE, Component::Transform(Component::Vector2Df(5600, 400), 0, Component::Vector2Df(1,1)));
        r.emplaceComponent<Component::Transform>(spawnerG, Component::Transform(Component::Vector2Df(7000, 100), 0, Component::Vector2Df(1,1)));
    }
    void Spawner::update(float deltaTime, Registry &r)
    {
        auto &tags = r.getComponents<Component::Tag>();

        for (Entity entity = 0; entity < tags.size(); entity++)
        {
            bool hasTag = r.hasComponent<Component::Tag>(entity);
            if (!hasTag)
                continue;
            auto &tag = r.getComponent<Component::Tag>(entity);
            if (tag.name != "spawner")
                continue;
            bool hasTransform = r.hasComponent<Component::Transform>(entity);
            if (!hasTransform)
                continue;
            auto &transform = r.getComponent<Component::Transform>(entity);
            transform.translate(-1000.f * deltaTime, 0.f);
            if (transform._position.x <= 1280)
            {
                auto enemyEntity = r.addEntity();
                auto enemyTransform = Component::Transform(Component::Vector2Df(transform._position.x, transform._position.y), -90, Component::Vector2Df(1,1));
                auto enemyShip = Component::Ship(Component::Ship::Type::Enemy);
                r.emplaceComponent<Component::Transform>(enemyEntity, enemyTransform);
                r.emplaceComponent<Component::Ship>(enemyEntity, enemyShip);
                r.emplaceComponent<Component::Collider>(enemyEntity, Component::Collider(Component::Rectangle(50,-60)));
                r.emplaceComponent<Component::Replication>(enemyEntity, Component::Replication(true, enemyEntity));
                transform._position.x += 6000;
            }
        }
    }

    void Spawner::stepUpdate(float deltaTime, Registry &r)
    {
    }
}