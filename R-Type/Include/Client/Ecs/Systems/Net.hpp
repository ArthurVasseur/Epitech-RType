/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** Net
*/

#ifndef Net_HPP_
#define Net_HPP_
#include <memory>
#include "ISystem.hpp"
#include "Registry.hpp"
#include "TcpClient.hpp"
#include "Text.hpp"
#include "Physics.hpp"
#include "Render.hpp"
#include "Transform.hpp"
#include "World.hpp"
#include "TextBox.hpp"
#include "UdpClient.hpp"

namespace System
{
    class Net : public ISystem
    {
    public:
        Net(std::shared_ptr<EventHandler> handler, Registry &r, const std::string &addr, short port, World &world);
        ~Net() = default;
        void update(float deltaTime, Registry &r);
        void udpUpdate(float deltaTime, Registry &r);
        void tcpUpdate(float deltaTime, Registry &r);
        void stepUpdate(float deltaTime, Registry &r);
        void onJoinById(Entity entity, Registry &r);
        void onCreateLobby();
        void loadLobby(Registry &r, short port);
        void loadGame(Registry &r, short port);
        void onQuit();
        void onStartGame();
        void onBackToNet(Registry &r);
        void loadNet(Registry &r);
        void newEntity(Registry &r, Network::UDP::Command cmd, const Network::UDP::NetworkedComponent &udpComp);
        void setEntitySprite(Registry &r, Network::UDP::Command cmd, Entity newEntity);
    protected:
    private:
        std::unique_ptr<Network::TCP::TcpClient> _tcpClient;
        std::shared_ptr<Network::UDP::UdpClient> _udpClient;
        std::shared_ptr<EventHandler> _handler;
        World &_world;
        std::string _addr;
    };
}

#endif /* !Net_HPP_ */
