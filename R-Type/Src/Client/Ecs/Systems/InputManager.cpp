/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** InputManager
*/

#include "InputManager.hpp"

namespace System
{
    InputManager::InputManager(std::shared_ptr<EventHandler> handler, std::shared_ptr<Network::UDP::UdpClient> udpClient) : _udpClient(udpClient)
    {
        handler->addKeyToHandle(Input::Up);
        handler->addKeyToHandle(Input::Left);
        handler->addKeyToHandle(Input::Right);
        handler->addKeyToHandle(Input::Down);
        handler->addKeyToHandle(Input::Space);
        handler->addInputHandler([this](std::map<Input::Key, bool> &inputs, float deltaTime, Registry &r)
                                 {
                                     if (inputs[Input::Up])
                                     {
                                         Network::UDP::Packet pkt(MAGIC_NUMBER, (std::uint32_t)Network::UDP::Command::Input, 0, Input::Up);
                                         _udpClient->write(pkt);
                                     }
                                     if (inputs[Input::Down])
                                     {
                                         Network::UDP::Packet pkt(MAGIC_NUMBER, (std::uint32_t)Network::UDP::Command::Input, 0, Input::Down);
                                         _udpClient->write(pkt);
                                     }
                                     if (inputs[Input::Left])
                                     {
                                         Network::UDP::Packet pkt(MAGIC_NUMBER, (std::uint32_t)Network::UDP::Command::Input, 0, Input::Left);
                                         _udpClient->write(pkt);
                                     }
                                     if (inputs[Input::Right])
                                     {
                                         Network::UDP::Packet pkt(MAGIC_NUMBER, (std::uint32_t)Network::UDP::Command::Input, 0, Input::Right);
                                         _udpClient->write(pkt);
                                     }
                                     if (inputs[Input::Space])
                                     {
                                         Network::UDP::Packet pkt(MAGIC_NUMBER, (std::uint32_t)Network::UDP::Command::Input, 0, Input::Space);
                                         _udpClient->write(pkt);
                                     }
                                 });
    }

    InputManager::~InputManager()
    {
    }

    void InputManager::update(float deltaTime, Registry &r)
    {
    }

    void InputManager::stepUpdate(float deltaTime, Registry &r)
    {
    }
} // namespace System
