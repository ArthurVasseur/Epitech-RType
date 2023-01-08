/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** Shot
*/

#include "Shot.hpp"
#include "Transform.hpp"
#include "Tag.hpp"

namespace System
{
    void Shot::update(float deltaTime, Registry &r)
    {
        auto &tags = r.getComponents<Component::Tag>();

        for (Entity entity = 0; entity < tags.size(); entity++)
        {
            try
            {
                bool hasTag = r.hasComponent<Component::Tag>(entity);
                if (!hasTag)
                    continue;
                auto &tag = r.getComponent<Component::Tag>(entity);
                if (tag.name != "shot")
                    continue;
                bool hasTransform = r.hasComponent<Component::Transform>(entity);
                if (!hasTransform)
                    continue;
                auto &transform = r.getComponent<Component::Transform>(entity);
                if (transform._rotation == 90)
                    transform.translate(1000.f * deltaTime, 0.f);
                else
                    transform.translate(-1000.f * deltaTime, 0.f);
                if (transform._position.x > 1280 || transform._position.x < -20)
                {
                    r.removeEntity(entity);
                }
            }

            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
                continue;
            }
        }
    }
    void Shot::stepUpdate(float deltaTime, Registry &r)
    {
    }
}