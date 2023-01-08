/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** Ecs
*/

#include <gtest/gtest.h>
#include <cstring>
#include "Registry.hpp"
#include "Transform.hpp"

TEST(Registry, AddEntity)
{
    Registry r;
    Entity entity = r.addEntity();
    EXPECT_EQ(0, entity);
    entity = r.addEntity();
    EXPECT_EQ(1, entity);
    r.removeEntity(entity);
    entity = r.addEntity();
    EXPECT_EQ(1, entity);
}

TEST(Registry, addComponent)
{
    Registry r;
    Entity entity = r.addEntity();
    auto &comp = r.emplaceComponent<Component::Transform>(entity, Component::Transform(Component::Vector2Df(0, 0), 0, Component::Vector2Df(0, 0)));
    auto &comp2 = r.getComponent<Component::Transform>(entity);
    EXPECT_EQ(0, std::memcmp(&comp.value(), &comp2, sizeof(Component::Transform)));
}

TEST(Registry, addComponent2)
{
    Registry r;
    Entity entity = r.addEntity();
    auto &comp = r.emplaceComponent<Component::Transform>(entity, Component::Transform(Component::Vector2Df(0, 0), 0, Component::Vector2Df(0, 0)));
    auto &comp2 = r.getComponent<Component::Transform>(entity);
    EXPECT_EQ(0, std::memcmp(&comp.value(), &comp2, sizeof(Component::Transform)));
}

TEST(Registry, removeComponent)
{
    Registry r;
    Entity entity = r.addEntity();
    auto &comp = r.emplaceComponent<Component::Transform>(entity, Component::Transform(Component::Vector2Df(0, 0), 0, Component::Vector2Df(0, 0)));

    try
    {
        r.removeComponent<Component::Transform>(entity);
        SUCCEED();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        FAIL();
    }
}

TEST(Registry, removeComponent2)
{
    Registry r;
    Entity entity = r.addEntity();

    try
    {
        r.removeComponent<Component::Transform>(entity);
        FAIL();
    }
    catch (const std::exception &e)
    {
        SUCCEED();
    }
}