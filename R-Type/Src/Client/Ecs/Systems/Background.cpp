/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** Background
*/

#include "Background.hpp"
#include "Transform.hpp"
#include "Tag.hpp"
#include "Sprite.hpp"

namespace System
{

    Background::Background(Registry &r)
    {
        auto backgroundEntity = r.addEntity();
        auto backgroundEntity2 = r.addEntity();
        auto planetEntity = r.addEntity();
        auto planetEntity2 = r.addEntity();

        auto transform = Component::Transform(Component::Vector2Df(0, 0), 0, Component::Vector2Df(1, 1));
        r.emplaceComponent<Component::Transform>(backgroundEntity, transform);
        auto textureBackground = Component::Sprite("./assets/background/bg.png");
        r.emplaceComponent<Component::Sprite>(backgroundEntity, textureBackground);
        auto tag = Component::Tag("background");
        r.emplaceComponent<Component::Tag>(backgroundEntity, tag);
        auto transform2 = Component::Transform(Component::Vector2Df(1300, 0), 0, Component::Vector2Df(1, 1));
        r.emplaceComponent<Component::Transform>(backgroundEntity2, transform2);
        auto textureBackground2 = Component::Sprite("./assets/background/bg.png");
        r.emplaceComponent<Component::Sprite>(backgroundEntity2, textureBackground2);
        auto tag2 = Component::Tag("background");
        r.emplaceComponent<Component::Tag>(backgroundEntity2, tag2);

        auto transform3 = Component::Transform(Component::Vector2Df(1300, 50), 0, Component::Vector2Df(2, 2));
        r.emplaceComponent<Component::Transform>(planetEntity, transform3);
        auto textureBackground3 = Component::Sprite("./assets/background/planet.png");
        r.emplaceComponent<Component::Sprite>(planetEntity, textureBackground3);
        auto tag3 = Component::Tag("planet");
        r.emplaceComponent<Component::Tag>(planetEntity, tag3);

        auto transform4 = Component::Transform(Component::Vector2Df(500, 300), 0, Component::Vector2Df(0.80, 0.80));
        r.emplaceComponent<Component::Transform>(planetEntity2, transform4);
        auto textureBackground4 = Component::Sprite("./assets/background/planet1.png");
        r.emplaceComponent<Component::Sprite>(planetEntity2, textureBackground4);
        auto tag4 = Component::Tag("planet");
        r.emplaceComponent<Component::Tag>(planetEntity2, tag4);
    }

    void Background::update(float deltaTime, Registry &r)
    {
        auto &transforms = r.getComponents<Component::Transform>();
        for (Entity entity = 0; entity < transforms.size(); entity++)
        {
            try
            {
                if (!r.hasComponent<Component::Transform>(entity))
                    continue;
                if (!r.hasComponent<Component::Tag>(entity))
                    continue;
                auto &tag = r.getComponent<Component::Tag>(entity);
                if (tag.name != "background" && tag.name != "planet")
                    continue;
                if (tag.name == "background")
                {
                    auto &transform = r.getComponent<Component::Transform>(entity);
                    transform.translate(-80.f * deltaTime, 0);
                    if (transform._position.x <= -1300)
                        transform._position.x = 1300;
                }
                if (tag.name == "planet")
                {
                    auto &transform = r.getComponent<Component::Transform>(entity);
                    transform.translate(-10.f * deltaTime, 0);
                    if (transform._position.x <= -100)
                        r.removeEntity(entity);
                }
            }
            catch (const std::exception &e)
            {
            }
        }
    }
    void Background::loadBackground(Registry &r)
    {
        auto backgroundEntity = r.addEntity();
        auto backgroundEntity2 = r.addEntity();
        auto planetEntity = r.addEntity();
        auto planetEntity2 = r.addEntity();

        auto transform = Component::Transform(Component::Vector2Df(0, 0), 0, Component::Vector2Df(1, 1));
        r.emplaceComponent<Component::Transform>(backgroundEntity, transform);
        auto textureBackground = Component::Sprite("./assets/background/bg.png");
        r.emplaceComponent<Component::Sprite>(backgroundEntity, textureBackground);
        auto tag = Component::Tag("background");
        r.emplaceComponent<Component::Tag>(backgroundEntity, tag);
        auto transform2 = Component::Transform(Component::Vector2Df(1300, 0), 0, Component::Vector2Df(1, 1));
        r.emplaceComponent<Component::Transform>(backgroundEntity2, transform2);
        auto textureBackground2 = Component::Sprite("./assets/background/bg.png");
        r.emplaceComponent<Component::Sprite>(backgroundEntity2, textureBackground2);
        auto tag2 = Component::Tag("background");
        r.emplaceComponent<Component::Tag>(backgroundEntity2, tag2);

        auto transform3 = Component::Transform(Component::Vector2Df(1300, 50), 0, Component::Vector2Df(2, 2));
        r.emplaceComponent<Component::Transform>(planetEntity, transform3);
        auto textureBackground3 = Component::Sprite("./assets/background/planet.png");
        r.emplaceComponent<Component::Sprite>(planetEntity, textureBackground3);
        auto tag3 = Component::Tag("planet");
        r.emplaceComponent<Component::Tag>(planetEntity, tag3);

        auto transform4 = Component::Transform(Component::Vector2Df(500, 300), 0, Component::Vector2Df(0.80, 0.80));
        r.emplaceComponent<Component::Transform>(planetEntity2, transform4);
        auto textureBackground4 = Component::Sprite("./assets/background/planet1.png");
        r.emplaceComponent<Component::Sprite>(planetEntity2, textureBackground4);
        auto tag4 = Component::Tag("planet");
        r.emplaceComponent<Component::Tag>(planetEntity2, tag4);
    }

    void Background::stepUpdate(float deltaTime, Registry &r)
    {
    }
}
