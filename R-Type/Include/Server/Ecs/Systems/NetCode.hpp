/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** NetCode
*/

#ifndef NETCODE_HPP_
#define NETCODE_HPP_
#include <unordered_map>
#include <queue>
#include "ISystem.hpp"
#include "UdpServer.hpp"
#include "Packet.hpp"
#include "Input.hpp"

namespace System
{
    class NetCode : public ISystem
    {
    public:
        NetCode(short port);
        ~NetCode();
        void update(float deltaTime, Registry &r);
        void stepUpdate(float deltaTime, Registry &r);
        void onNewData(Registry &r, float deltaTime, const Network::UDP::Packet &pkt);
        void manageInputs(Registry &r, Input::Key input, float deltaTime, const Network::UDP::Packet &pkt);

    protected:
    private:
        Network::UDP::Server _server;
        std::queue<Network::UDP::Command> _availableColor;
        std::unordered_map<std::uint8_t, std::pair<Entity, Network::UDP::Command>> _entityPlayerRelations;
        std::size_t _maxId;
        int lastFirePosX = 20;
        int lastFirePosY = -1;
        int newFirePosX = 20;
        int newFirePosY = 25;
    };
} // namespace System

#endif /* !NETCODE_HPP_ */
