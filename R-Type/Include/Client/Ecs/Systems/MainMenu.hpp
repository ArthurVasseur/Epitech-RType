/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** MainMenu
*/

#ifndef MAINMENU_HPP_
#define MAINMENU_HPP_
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
    class MainMenu : public ISystem
    {
    public:
        MainMenu(std::shared_ptr<EventHandler> handler, Registry &r, const std::string &addr, short port, World &world);
        ~MainMenu() = default;
        void update(float deltaTime, Registry &r);
        void stepUpdate(float deltaTime, Registry &r);
        void onJoinById(Entity entity, Registry &r);
        void onCreateLobby();
        void loadLobby(Registry &r, short port);
        void loadGame(Registry &r, short port);
        void onQuit();
        void onStartGame();
        void onBackToMainMenu(Registry &r);
        void loadMainMenu(Registry &r);
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

#endif /* !MAINMENU_HPP_ */
