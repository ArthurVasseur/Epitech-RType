/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** Collisions
*/

#include "Collisions.hpp"
#include "Transform.hpp"
#include "Tag.hpp"
#include "Collider.hpp"
#include "Ship.hpp"

namespace System
{
    void Collisions::update(float deltaTime, Registry &r)
    {
        auto &colliders = r.getComponents<Component::Collider>();
        for (Entity entityA = 0; entityA < colliders.size(); entityA++)
        {
            bool hasColliderA = r.hasComponent<Component::Collider>(entityA);
            if (!hasColliderA)
                continue;
            auto &colliderA = r.getComponent<Component::Collider>(entityA);
            bool hasShipA = r.hasComponent<Component::Ship>(entityA);
            if (!hasShipA)
                continue;
            auto &shipA = r.getComponent<Component::Ship>(entityA);
            auto &transformA = r.getComponent<Component::Transform>(entityA);
            for (Entity entityB = 1 + entityA; entityB < colliders.size(); entityB++)
            {
                bool hasColliderB = r.hasComponent<Component::Collider>(entityB);
                if (!hasColliderB)
                    continue;
                auto &colliderB = r.getComponent<Component::Collider>(entityB);
                auto &transformB = r.getComponent<Component::Transform>(entityB);
                if (!Component::Collider::checkCollision(transformA._position, colliderA.getRectangle(), transformB._position, colliderB.getRectangle()))
                    continue;

                if (r.hasComponent<Component::Ship>(entityB))
                {
                    auto &shipB = r.getComponent<Component::Ship>(entityB);
                    if (shipA._type != shipB._type)
                    {
                        r.removeEntity(entityA);
                        r.removeEntity(entityB);
                    }
                    continue;
                }
                auto &tag = r.getComponent<Component::Tag>(entityB);
                if (tag.name == "shot" || tag.name == "enemyShot")
                {
                    if (transformB._rotation == 90 && shipA._type == shipA.Enemy)
                    {
                        r.removeEntity(entityA);
                        r.removeEntity(entityB);
                    }
                    else if (transformB._rotation == -90 && shipA._type == shipA.Player)
                    {
                        r.removeEntity(entityA);
                        r.removeEntity(entityB);
                    }
                }
            }
        }
    }

    void Collisions::stepUpdate(float deltaTime, Registry &r)
    {
    }
}