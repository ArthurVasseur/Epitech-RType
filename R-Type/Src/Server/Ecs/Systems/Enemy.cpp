/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** Render
*/

#include "Enemy.hpp"
#include "Transform.hpp"
#include "Ship.hpp"
#include "Tag.hpp"
#include "Collider.hpp"
#include "Replication.hpp"

namespace System
{
    void Enemy::update(float deltaTime, Registry &r)
    {
        auto &ships = r.getComponents<Component::Ship>();

        for (std::size_t entity = 0; entity < ships.size(); entity++)
        {
            bool hasShip = r.hasComponent<Component::Ship>(entity);
            if (!hasShip)
                continue;
            auto &ship = r.getComponent<Component::Ship>(entity);
            if (ship._type != Component::Ship::Type::Enemy)
                continue;
            bool hasTransform = r.hasComponent<Component::Transform>(entity);
            if (!hasTransform)
                continue;
            auto &transform = r.getComponent<Component::Transform>(entity);
            transform.translate(-100.f * deltaTime, 0.f);
            auto &replication = r.getComponent<Component::Replication>(entity);
            std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
            replication._lastUpdate = now;
            if (std::chrono::duration_cast<std::chrono::milliseconds>(now - ship.lastShot).count() >= 2000)
            {
                ship.lastShot = now;
                auto shot = r.addEntity();
                auto shotTransform = Component::Transform(Component::Vector2Df(transform._position.x, transform._position.y - 28), -90, Component::Vector2Df(1, 1));
                auto tag = Component::Tag("enemyShot");
                r.emplaceComponent<Component::Transform>(shot, shotTransform);
                r.emplaceComponent<Component::Tag>(shot, tag);
                r.emplaceComponent<Component::Collider>(shot, Component::Collider(Component::Rectangle(15,-15)));
            }
            if (transform._position.x < -50)
                r.removeEntity(entity);
        }
    }

    void Enemy::stepUpdate(float deltaTime, Registry &r)
    {
    }
}