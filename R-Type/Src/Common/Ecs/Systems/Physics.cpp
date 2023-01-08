/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** Physics
*/

#include "Physics.hpp"
#include "RigidBody2D.hpp"
#include "Transform.hpp"
#include "Collider.hpp"

namespace System
{

    void Physics::update(float deltatime, Registry &r)
    {
    }

    void Physics::stepUpdate(float deltatime, Registry &r)
    {
        try
        {
            auto &transforms = r.getComponents<Component::Transform>();
            for (std::size_t entity = 0; entity < transforms.size(); entity++)
            {
                if (!r.hasComponent<Component::RigidBody2D>(entity))
                    continue;
                auto &transform = r.getComponent<Component::Transform>(entity);
                auto &rigidBody = r.getComponent<Component::RigidBody2D>(entity);
                rigidBody.addForce(_gravity);
                const Component::Vector2Df oldVelocity = rigidBody.getVelocity();
                Component::Vector2Df acceleration = rigidBody.getForces() * rigidBody.getInvMass();
                Component::Vector2Df velocity = rigidBody.getVelocity() * _friction + acceleration * deltatime;
                rigidBody.setVelocity(velocity);
            }
            for (Entity entity = 0; entity < transforms.size(); entity++)
            {
                if (!r.hasComponent<Component::RigidBody2D>(entity))
                    continue;
                bool isColliding = false;
                auto &transform = r.getComponent<Component::Transform>(entity);
                auto &collider = r.getComponent<Component::Collider>(entity);
                auto &pos = transform._position;
                for (Entity entityCollider = 0; entityCollider < transforms.size(); entityCollider++)
                {
                    if (!r.hasComponent<Component::Collider>(entityCollider))
                        continue;
                    if (entityCollider == entity)
                        continue;
                    if (collider.checkCollision(transform._position, r.getComponent<Component::Collider>(entityCollider), r.getComponent<Component::Transform>(entityCollider)._position))
                    {
                        isColliding = true;
                        break;
                    }
                }
                if (isColliding)
                    continue;
                if (!r.hasComponent<Component::RigidBody2D>(entity))
                    continue;
                transform.translate({0.f, 100.f * deltatime});
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}