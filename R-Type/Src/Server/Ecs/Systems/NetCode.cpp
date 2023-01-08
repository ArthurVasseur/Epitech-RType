/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** NetCode
*/

#include <algorithm>
#include "NetCode.hpp"
#include "Registry.hpp"
#include "Transform.hpp"
#include "Replication.hpp"
#include "Input.hpp"
#include "Ship.hpp"
#include "Tag.hpp"
#include "Collider.hpp"
namespace System
{
    NetCode::NetCode(short port) : _server(port)
    {
        _availableColor.push(Network::UDP::Command::PlayerR);
        _availableColor.push(Network::UDP::Command::PlayerG);
        _availableColor.push(Network::UDP::Command::PlayerY);
        _availableColor.push(Network::UDP::Command::PlayerB);
    }

    NetCode::~NetCode()
    {
    }

    void NetCode::update(float deltaTime, Registry &r)
    {
        _server.startOnce();
    }

    void NetCode::stepUpdate(float deltaTime, Registry &r)
    {
        try
        {
            auto &replications = r.getComponents<Component::Replication>();
            for (Entity entity = 0; entity < replications.size(); entity++)
            {
                bool hasReplication = r.hasComponent<Component::Replication>(entity);
                bool hasTransform = r.hasComponent<Component::Transform>(entity);
                if (!hasTransform)
                    continue;
                bool hasShip = r.hasComponent<Component::Ship>(entity);
                bool hasTag = r.hasComponent<Component::Tag>(entity);
                auto &transform = r.getComponent<Component::Transform>(entity);
                Network::UDP::NetworkedComponent comp(entity, transform);
                Network::UDP::Packet pkt(MAGIC_NUMBER, (std::uint32_t)Network::UDP::Command::PlayerR, _maxId++, comp);
                if (hasShip)
                {
                    auto &ship = r.getComponent<Component::Ship>(entity);
                    if (ship._type == Component::Ship::Type::Enemy)
                        pkt._commandId = (std::uint32_t)Network::UDP::Command::Enemy;
                    else
                    {
                        auto it = std::find_if(_entityPlayerRelations.begin(), _entityPlayerRelations.end(), [entity](std::pair<std::uint8_t, std::pair<Entity, Network::UDP::Command>> user)
                                                                 { return user.second.first == entity;});
                        pkt._commandId = (std::uint32_t)it->second.second;
                    }
                    auto &replication = r.getComponent<Component::Replication>(entity);
                    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - replication._lastUpdate).count() >= 3000)
                        continue;
                    else
                        _server.writeAll(pkt);
                }
                if (hasTag)
                {
                    auto &tag = r.getComponent<Component::Tag>(entity);
                    if (tag.name == "shot")
                        pkt._commandId = (std::uint32_t)Network::UDP::Command::PlayerShot;
                    if (tag.name == "enemyShot") {
                        pkt._commandId = (std::uint32_t)Network::UDP::Command::EnemyShot;
                    }
                    _server.writeAll(pkt);
                }
            }
        }
        catch (const std::exception &e)
        {
        }

        Network::UDP::Packet pkt;
        while (_server.poll(pkt))
        {
            onNewData(r, deltaTime, pkt);
        }
    }

    void NetCode::onNewData(Registry &r, float deltaTime, const Network::UDP::Packet &pkt)
    {
        switch ((Network::UDP::Command)pkt._commandId)
        {
        case Network::UDP::Command::Input:
        {
            Network::Port key;
            key << pkt._data;
            manageInputs(r, (Input::Key)key._port, deltaTime, pkt);
            break;
        }
        }
    }

    void NetCode::manageInputs(Registry &r, Input::Key input, float deltaTime, const Network::UDP::Packet &pkt)
    {
        auto it = _entityPlayerRelations.find(pkt._senderId);
        if (it == _entityPlayerRelations.end())
        {
            auto entity = r.addEntity();
            r.emplaceComponent<Component::Transform>(entity, Component::Transform(Component::Vector2Df(100, 200), 90, Component::Vector2Df(1, 1)));
            r.emplaceComponent<Component::Replication>(entity, Component::Replication(true, entity));
            r.emplaceComponent<Component::Ship>(entity, Component::Ship(Component::Ship::Player));
            r.emplaceComponent<Component::Collider>(entity, Component::Collider(Component::Rectangle(-30,35)));
            _entityPlayerRelations[pkt._senderId] = {entity, _availableColor.front()};
            _availableColor.pop();
        }
        else
        {
            Entity entity = it->second.first;
            auto &transform = r.getComponent<Component::Transform>(entity);
            auto &ship = r.getComponent<Component::Ship>(entity);
            auto &replication = r.getComponent<Component::Replication>(entity);
            replication._lastUpdate = std::chrono::steady_clock::now();
            if (input == Input::Up)
            {
                transform.translate(0.f, -400.f * deltaTime);
                if (transform._position.y < 0)
                    transform._position.y = 0;
            }
            if (input == Input::Down)
            {
                transform.translate(0.f, 400.f * deltaTime);
                if (transform._position.y + 50 > 720)
                    transform._position.y = 670;
            }
            if (input == Input::Left)
            {
                transform.translate(-400.f * deltaTime, 0.f);
                if (transform._position.x - 50 < 0)
                    transform._position.x = 50;
            }
            if (input == Input::Right)
            {
                transform.translate(400.f * deltaTime, 0.f);
                if (transform._position.x > 1280)
                    transform._position.x = 1280;
            }
            std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
            if (input == Input::Space && std::chrono::duration_cast<std::chrono::milliseconds>(now - ship.lastShot).count() >= 200)
            {
                ship.lastShot = now;
                int firePosX = newFirePosX;
                int firePosY = newFirePosY;
                auto shot = r.addEntity();
                auto shotTransform = Component::Transform(Component::Vector2Df(transform._position.x + firePosX, transform._position.y + firePosY), 90, Component::Vector2Df(1, 1));
                newFirePosX = lastFirePosX;
                newFirePosY = lastFirePosY;
                lastFirePosX = firePosX;
                lastFirePosY = firePosY;
                r.emplaceComponent<Component::Transform>(shot, shotTransform);
                r.emplaceComponent<Component::Tag>(shot, Component::Tag("shot"));
                r.emplaceComponent<Component::Replication>(shot, Component::Replication(true, shot));
                r.emplaceComponent<Component::Collider>(shot, Component::Collider(Component::Rectangle(-15,15)));
            }
        }
    }
}
