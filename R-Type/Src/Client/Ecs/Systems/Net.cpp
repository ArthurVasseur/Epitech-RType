/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** Net
*/

#include <iostream>
#include <string>
#include "Net.hpp"
#include "Button.hpp"
#include "Transform.hpp"
#include "Rectangle.hpp"
#include "Text.hpp"
#include "Replication.hpp"
#include "Background.hpp"
#include "Tag.hpp"
#include "InputManager.hpp"
#include "AudioSource.hpp"
#include "Background.hpp"
#include "Collider.hpp"

namespace System
{
    static const std::map<Network::UDP::Command, std::string> color = {{Network::UDP::Command::PlayerR, "./assets/playerR.png"}, {Network::UDP::Command::PlayerG, "./assets/playerG.png"}, {Network::UDP::Command::PlayerY, "./assets/playerY.png"}, {Network::UDP::Command::PlayerB, "./assets/playerB.png"}};
    Net::Net(std::shared_ptr<EventHandler> handler, Registry &r, const std::string &addr, short port, World &world) : _tcpClient(std::make_unique<Network::TCP::TcpClient>(addr, port)), _world(world), _handler(handler), _addr(addr)
    {
        loadNet(r);
    }

    void Net::update(float deltaTime, Registry &r)
    {
        try
        {
            tcpUpdate(deltaTime, r);
            udpUpdate(deltaTime, r);
        }
        catch (const std::exception &e)
        {
        }
    }

    void Net::udpUpdate(float deltaTime, Registry &r)
    {
        Network::UDP::Packet udpPkt;
        if (_udpClient)
            _udpClient->startOnce();
        while (_udpClient && _udpClient->poll(udpPkt))
        {
            Network::UDP::NetworkedComponent udpComp;
            udpComp << udpPkt._data;
            bool found = false;
            try
            {
                auto &replications = r.getComponents<Component::Replication>();
                for (Entity entity = 0; entity < replications.size(); entity++)
                {
                    bool hasReplication = r.hasComponent<Component::Replication>(entity);
                    bool hasTransform = r.hasComponent<Component::Transform>(entity);
                    if (!hasReplication || !hasTransform)
                        continue;
                    auto &replication = r.getComponent<Component::Replication>(entity);
                    auto &transform = r.getComponent<Component::Transform>(entity);
                    if (replication._id == udpComp._id)
                    {
                        std::memcpy(&transform, udpComp._data.data(), sizeof(Component::Transform));
                        found = true;
                        setEntitySprite(r, (Network::UDP::Command)udpPkt._commandId, entity);
                        replication._lastUpdate = std::chrono::steady_clock::now();
                    }
                    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
                    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - replication._lastUpdate).count() >= 100)
                        r.removeEntity(entity);
                }
            }
            catch (const std::exception &e)
            {
            }
            if (!found)
                newEntity(r, (Network::UDP::Command)udpPkt._commandId, udpComp);
        }
    }

    void Net::tcpUpdate(float deltaTime, Registry &r)
    {
        if (_tcpClient && _tcpClient->isConnected() && _tcpClient->getContext().stopped())
            _tcpClient->getContext().restart();
        if (_tcpClient && _tcpClient->isConnected())
            _tcpClient->getContext().poll();
        if (_tcpClient && _tcpClient->isConnected() == false)
            _tcpClient->connect();
        Network::TCP::Packet tcpkt;
        while (_tcpClient && _tcpClient->poll(tcpkt))
        {
            switch ((Network::TCP::Command::Server)tcpkt._commandId)
            {
            case Network::TCP::Command::Server::LobbyPort:
            {
                Network::Port lPort;
                lPort << tcpkt._data;
                loadLobby(r, lPort._port);
                break;
            }
            case Network::TCP::Command::Server::StartingGame:
            {
                Network::Port lPort;
                lPort << tcpkt._data;
                loadGame(r, lPort._port);
                break;
            }
            case Network::TCP::Command::Server::PlayerConnect:
            {
                Network::Port port;
                port << tcpkt._data;
                auto &tags = r.getComponents<Component::Tag>();
                for (Entity entity = 0; entity < tags.size(); entity++)
                {
                    if (!r.hasComponent<Component::Tag>(entity))
                        continue;
                    auto &tag = r.getComponent<Component::Tag>(entity);
                    auto str = std::string("player") + std::to_string(port._port + 1);
                    if (tag.name == str)
                    {
                        auto &txt = r.getComponent<Component::ui::Text>(entity);
                        txt._color = Component::ui::Color(255, 255, 255);
                        break;
                    }
                }
                break;
            }
            case Network::TCP::Command::Server::PlayerDisconnect:
            {
                Network::Port port;
                port << tcpkt._data;

                auto &tags = r.getComponents<Component::Tag>();
                for (Entity entity = 0; entity < tags.size(); entity++)
                {
                    if (!r.hasComponent<Component::Tag>(entity))
                        continue;
                    auto &tag = r.getComponent<Component::Tag>(entity);
                    if (tag.name == std::string("player") + std::to_string(port._port + 1))
                    {
                        auto &txt = r.getComponent<Component::ui::Text>(entity);
                        txt._color = Component::ui::Color(127, 127, 127);
                        break;
                    }
                }
                break;
            }
            break;
            }
        }
    }

    void Net::newEntity(Registry &r, Network::UDP::Command cmd, const Network::UDP::NetworkedComponent &udpComp)
    {
        Entity newEntity = r.addEntity();
        auto &t = r.emplaceComponent<Component::Transform>(newEntity, Component::Transform(Component::Vector2Df(0, 0), 0, Component::Vector2Df(0, 0)));
        std::memcpy(&t, udpComp._data.data(), sizeof(Component::Transform));
        setEntitySprite(r, cmd, newEntity);
        r.emplaceComponent<Component::Replication>(newEntity, Component::Replication(true, udpComp._id));
    }

    void Net::setEntitySprite(Registry &r, Network::UDP::Command cmd, Entity newEntity)
    {
        if (cmd >= Network::UDP::Command::PlayerR && cmd <= Network::UDP::Command::PlayerB)
        {
            if (r.hasComponent<Component::Sprite>(newEntity))
            {
                auto &sprite = r.getComponent<Component::Sprite>(newEntity);
                sprite._path = color.find(cmd)->second;
            }
            else
                r.emplaceComponent<Component::Sprite>(newEntity, Component::Sprite(color.find(cmd)->second));
        }
        if (cmd == Network::UDP::Command::PlayerShot)
        {
            if (r.hasComponent<Component::Sprite>(newEntity))
            {
                auto &sprite = r.getComponent<Component::Sprite>(newEntity);
                sprite._path = "./assets/shots/1.png";
            }
            else
                r.emplaceComponent<Component::Sprite>(newEntity, Component::Sprite("./assets/shots/1.png"));
            if (!r.hasComponent<Component::AudioSource>(newEntity))
            {
                r.emplaceComponent<Component::AudioSource>(newEntity, Component::AudioSource("./assets/music/shot.wav", true, false, Component::AudioSource::Type::SOUND));
            }
        }
        if (cmd == Network::UDP::Command::Enemy)
        {
            if (r.hasComponent<Component::Sprite>(newEntity))
            {
                auto &sprite = r.getComponent<Component::Sprite>(newEntity);
                sprite._path = "./assets/Enemy1.png";
            }
            else
                r.emplaceComponent<Component::Sprite>(newEntity, Component::Sprite("./assets/Enemy2.png"));
        }
        if (cmd == Network::UDP::Command::EnemyShot)
        {
            if (r.hasComponent<Component::Sprite>(newEntity))
            {
                auto &sprite = r.getComponent<Component::Sprite>(newEntity);
                sprite._path = "./assets/shots/3.png";
            }
            else
                r.emplaceComponent<Component::Sprite>(newEntity, Component::Sprite("./assets/shots/3.png"));
            if (!r.hasComponent<Component::AudioSource>(newEntity))
            {
                r.emplaceComponent<Component::AudioSource>(newEntity, Component::AudioSource("./assets/music/shot.wav", true, false, Component::AudioSource::Type::SOUND));
            }
        }
    }

    void Net::loadGame(Registry &r, short port)
    {
        _tcpClient.reset();
        r.clear();
        _udpClient = std::make_shared<Network::UDP::UdpClient>(_addr, port);
        Network::UDP::Packet pkt(MAGIC_NUMBER, 0, 0);
        _udpClient->write(pkt);

        System::Background::loadBackground(r);
        _world.addSystem<System::InputManager>(_handler, _udpClient);
        auto btnBackToNetEntity = r.addEntity();
        r.emplaceComponent<Component::Transform>(btnBackToNetEntity, Component::Transform(Component::Vector2Df(1200, 25), 0, Component::Vector2Df(0.25f, 1)));
        r.emplaceComponent<Component::ui::Button>(btnBackToNetEntity, Component::ui::Button([&r, this]()
                                                                                            { this->onBackToNet(r); },
                                                                                            []() {}, []() {}));
        r.emplaceComponent<Component::Rectangle>(btnBackToNetEntity, Component::Vector2Df(256, 43));
        auto btnSprite2 = Component::Sprite("./assets/Btn.png");
        auto btnTxt = r.addEntity();
        r.emplaceComponent<Component::Transform>(btnTxt, Component::Transform(Component::Vector2Df(1201, 22), 0, Component::Vector2Df(1.f, 1)));
        r.emplaceComponent<Component::Sprite>(btnBackToNetEntity, btnSprite2);
        r.emplaceComponent<Component::ui::Text>(btnTxt, Component::ui::Text(std::string("./assets/pixelated.ttf"), std::string(" X"), Component::ui::Color(0, 0, 0), 40));
    }

    void Net::stepUpdate(float deltaTime, Registry &r)
    {
    }

    void Net::onJoinById(Entity entity, Registry &r)
    {
        try
        {
            auto &txt = r.getComponent<Component::ui::Text>(entity);
            loadLobby(r, std::stoi(txt._text));
        }
        catch (const std::exception &e)
        {
            return;
        }
    }

    void Net::onStartGame()
    {
        Network::TCP::Packet pkt(MAGIC_NUMBER, (std::uint32_t)Network::TCP::Command::Client::StartGame);
        _tcpClient->write(pkt);
    }

    void Net::onCreateLobby()
    {
        Network::TCP::Packet pkt(MAGIC_NUMBER, (std::uint32_t)Network::TCP::Command::Client::CreateLobby);
        _tcpClient->write(pkt);
    }

    void Net::loadNet(Registry &r)
    {
        _udpClient.reset();
        auto btnCreateLobbyEntity = r.addEntity();
        r.emplaceComponent<Component::Transform>(btnCreateLobbyEntity, Component::Transform(Component::Vector2Df(100, 100), 0, Component::Vector2Df(1, 1)));
        r.emplaceComponent<Component::ui::Button>(btnCreateLobbyEntity, Component::ui::Button(
                                                                            std::bind(&Net::onCreateLobby, this), []() {}, []() {}));
        r.emplaceComponent<Component::Rectangle>(btnCreateLobbyEntity, Component::Vector2Df(256, 43));
        auto btnSprite1 = Component::Sprite("./assets/Btn.png");
        r.emplaceComponent<Component::Sprite>(btnCreateLobbyEntity, btnSprite1);
        r.emplaceComponent<Component::ui::Text>(btnCreateLobbyEntity, Component::ui::Text(std::string("./assets/pixelated.ttf"), std::string("   Create Lobby"), Component::ui::Color(0, 0, 0), 30));

        auto logoRtype = r.addEntity();
        Component::Transform transform2(Component::Vector2Df(850.f, 450.f), 0, Component::Vector2Df(1.5f, 1.5f));
        auto &tt2 = r.emplaceComponent<Component::Transform>(logoRtype, transform2);
        auto logoR = Component::Sprite("./assets/R-Type_Logo.png");
        auto &logoCmpnt = r.emplaceComponent<Component::Sprite>(logoRtype, logoR);

        auto btnQuitGameEntity = r.addEntity();
        r.emplaceComponent<Component::Transform>(btnQuitGameEntity, Component::Transform(Component::Vector2Df(100, 600), 0, Component::Vector2Df(1, 1)));
        r.emplaceComponent<Component::ui::Button>(btnQuitGameEntity, Component::ui::Button(
                                                                         std::bind(&Net::onQuit, this), []() {}, []() {}));
        r.emplaceComponent<Component::Rectangle>(btnQuitGameEntity, Component::Vector2Df(256, 43));
        auto btnSprite2 = Component::Sprite("./assets/Btn.png");
        r.emplaceComponent<Component::Sprite>(btnQuitGameEntity, btnSprite2);
        r.emplaceComponent<Component::ui::Text>(btnQuitGameEntity, Component::ui::Text(std::string("./assets/pixelated.ttf"), std::string("   Quit"), Component::ui::Color(0, 0, 0), 30));

        auto txtBoxJoinByIdEntity = r.addEntity();
        r.emplaceComponent<Component::Transform>(txtBoxJoinByIdEntity, Component::Transform(Component::Vector2Df(100, 300), 0, Component::Vector2Df(1, 1)));
        r.emplaceComponent<Component::Rectangle>(txtBoxJoinByIdEntity, Component::Vector2Df(256, 43));
        auto boxSprite = Component::Sprite("./assets/Text_box.png");
        r.emplaceComponent<Component::Sprite>(txtBoxJoinByIdEntity, boxSprite);
        r.emplaceComponent<Component::ui::Text>(txtBoxJoinByIdEntity, Component::ui::Text("./assets/pixelated.ttf", "", Component::ui::Color(255, 255, 255), 24));
        r.emplaceComponent<Component::ui::TextBox>(txtBoxJoinByIdEntity, Component::ui::TextBox(Component::Rectangle(256, 43)));
        auto btnJoinByIdEntity = r.addEntity();
        r.emplaceComponent<Component::Transform>(btnJoinByIdEntity, Component::Transform(Component::Vector2Df(100, 400), 0, Component::Vector2Df(1, 1)));
        r.emplaceComponent<Component::ui::Button>(btnJoinByIdEntity, Component::ui::Button([&r, txtBoxJoinByIdEntity, this]()
                                                                                           { onJoinById(txtBoxJoinByIdEntity, r); },
                                                                                           []() {}, []() {}));
        r.emplaceComponent<Component::Rectangle>(btnJoinByIdEntity, Component::Vector2Df(256, 43));
        auto btnSprite3 = Component::Sprite("./assets/Btn.png");
        r.emplaceComponent<Component::Sprite>(btnJoinByIdEntity, btnSprite3);
        r.emplaceComponent<Component::ui::Text>(btnJoinByIdEntity, Component::ui::Text(std::string("./assets/pixelated.ttf"), std::string("   Join"), Component::ui::Color(0, 0, 0), 30));
    }

    void Net::onBackToNet(Registry &r)
    {
        r.clear();
        System::Background::loadBackground(r);
        _tcpClient = std::make_unique<Network::TCP::TcpClient>(_addr, 2121);
        loadNet(r);
    }

    void Net::loadLobby(Registry &r, short port)
    {
        _tcpClient = std::make_unique<Network::TCP::TcpClient>(_addr, port);
        r.clear();
        System::Background::loadBackground(r);
        auto text = r.addEntity();
        Component::Transform transform(Component::Vector2Df(800.f, 0.f), 0, Component::Vector2Df(1.f, 1.f));
        auto &tt = r.emplaceComponent<Component::Transform>(text, transform);
        auto txt = Component::ui::Text("./assets/pixelated.ttf", "Lobby", Component::ui::Color(255, 255, 255), 75);
        auto &textcmpnt = r.emplaceComponent<Component::ui::Text>(text, txt);
        auto rectYellow = r.addEntity();
        Component::Transform transform2(Component::Vector2Df(550.f, 200.f), 90, Component::Vector2Df(1.f, 1.f));
        auto &tt2 = r.emplaceComponent<Component::Transform>(rectYellow, transform2);
        auto rectY = Component::Sprite("./assets/playerY.png");
        auto &rectYellowCmpnt = r.emplaceComponent<Component::Sprite>(rectYellow, rectY);
        auto text10 = r.addEntity();
        Component::Transform transform10(Component::Vector2Df(300.f, 185.f), 0, Component::Vector2Df(1.f, 1.f));
        auto &tt10 = r.emplaceComponent<Component::Transform>(text10, transform10);
        auto txt10 = Component::ui::Text("./assets/pixelated.ttf", "Player1", Component::ui::Color(127, 127, 127), 30);
        auto &textcmpnt10 = r.emplaceComponent<Component::ui::Text>(text10, txt10);
        r.emplaceComponent<Component::Tag>(text10, Component::Tag("player1"));
        auto rectRed = r.addEntity();
        Component::Transform transform3(Component::Vector2Df(600.f, 300.f), 90, Component::Vector2Df(1.f, 1.f));
        auto &tt3 = r.emplaceComponent<Component::Transform>(rectRed, transform3);
        auto rectR = Component::Sprite("./assets/playerR.png");
        auto &rectRedCmpnt = r.emplaceComponent<Component::Sprite>(rectRed, rectR);
        auto text11 = r.addEntity();
        Component::Transform transform11(Component::Vector2Df(300.f, 285.f), 0, Component::Vector2Df(1.f, 1.f));
        auto &tt11 = r.emplaceComponent<Component::Transform>(text11, transform11);
        auto txt11 = Component::ui::Text("./assets/pixelated.ttf", "Player2", Component::ui::Color(127, 127, 127), 30);
        auto &textcmpnt11 = r.emplaceComponent<Component::ui::Text>(text11, txt11);
        r.emplaceComponent<Component::Tag>(text11, Component::Tag("player2"));
        auto rectGreen = r.addEntity();
        Component::Transform transform4(Component::Vector2Df(600.f, 400.f), 90, Component::Vector2Df(1.f, 1.f));
        auto &tt4 = r.emplaceComponent<Component::Transform>(rectGreen, transform4);
        auto rectG = Component::Sprite("./assets/playerG.png");
        auto &rectGreenCmpnt = r.emplaceComponent<Component::Sprite>(rectGreen, rectG);
        auto text12 = r.addEntity();
        Component::Transform transform12(Component::Vector2Df(300.f, 385.f), 0, Component::Vector2Df(1.f, 1.f));
        auto &tt12 = r.emplaceComponent<Component::Transform>(text12, transform12);
        auto txt12 = Component::ui::Text("./assets/pixelated.ttf", "Player3", Component::ui::Color(127, 127, 127), 30);
        auto &textcmpnt12 = r.emplaceComponent<Component::ui::Text>(text12, txt12);
        r.emplaceComponent<Component::Tag>(text12, Component::Tag("player3"));
        auto rectPurple = r.addEntity();
        Component::Transform transform5(Component::Vector2Df(550.f, 500.f), 90, Component::Vector2Df(1.f, 1.f));
        auto &tt5 = r.emplaceComponent<Component::Transform>(rectPurple, transform5);
        auto rectP = Component::Sprite("./assets/playerB.png");
        auto &rectPurpleCmpnt = r.emplaceComponent<Component::Sprite>(rectPurple, rectP);
        auto text13 = r.addEntity();
        Component::Transform transform13(Component::Vector2Df(300.f, 490.f), 0, Component::Vector2Df(1.f, 1.f));
        auto &tt13 = r.emplaceComponent<Component::Transform>(text13, transform13);
        auto txt13 = Component::ui::Text("./assets/pixelated.ttf", "Player4", Component::ui::Color(127, 127, 127), 30);
        r.emplaceComponent<Component::Tag>(text13, Component::Tag("player4"));
        auto &textcmpnt13 = r.emplaceComponent<Component::ui::Text>(text13, txt13);

        auto btnCreateLobbyEntity = r.addEntity();
        r.emplaceComponent<Component::Transform>(btnCreateLobbyEntity, Component::Transform(Component::Vector2Df(800, 600), 0, Component::Vector2Df(1, 1)));
        r.emplaceComponent<Component::ui::Button>(btnCreateLobbyEntity, Component::ui::Button(
                                                                            std::bind(&Net::onStartGame, this), []() {}, []() {}));
        r.emplaceComponent<Component::Rectangle>(btnCreateLobbyEntity, Component::Vector2Df(256, 43));
        auto btnSprite1 = Component::Sprite("./assets/Btn.png");
        r.emplaceComponent<Component::Sprite>(btnCreateLobbyEntity, btnSprite1);
        r.emplaceComponent<Component::ui::Text>(btnCreateLobbyEntity, Component::ui::Text(std::string("./assets/pixelated.ttf"), std::string("   Start Game"), Component::ui::Color(0, 0, 0), 30));

        auto btnBackToNetEntity = r.addEntity();
        r.emplaceComponent<Component::Transform>(btnBackToNetEntity, Component::Transform(Component::Vector2Df(800, 500), 0, Component::Vector2Df(1, 1)));
        r.emplaceComponent<Component::ui::Button>(btnBackToNetEntity, Component::ui::Button([&r, this]()
                                                                                            { this->onBackToNet(r); },
                                                                                            []() {}, []() {}));
        r.emplaceComponent<Component::Rectangle>(btnBackToNetEntity, Component::Vector2Df(256, 43));
        auto btnSprite2 = Component::Sprite("./assets/Btn.png");
        r.emplaceComponent<Component::Sprite>(btnBackToNetEntity, btnSprite2);
        r.emplaceComponent<Component::ui::Text>(btnBackToNetEntity, Component::ui::Text(std::string("./assets/pixelated.ttf"), std::string("       BTTMM"), Component::ui::Color(0, 0, 0), 30));

        auto text20 = r.addEntity();
        Component::Transform transform20(Component::Vector2Df(800.f, 100.f), 0, Component::Vector2Df(1.f, 1.f));
        auto &tt20 = r.emplaceComponent<Component::Transform>(text20, transform20);
        auto txt20 = Component::ui::Text("./assets/pixelated.ttf", "ID :", Component::ui::Color(255, 255, 255), 25);
        auto &textcmpnt20 = r.emplaceComponent<Component::ui::Text>(text20, txt20);
        auto text21 = r.addEntity();
        Component::Transform transform21(Component::Vector2Df(900.f, 100.f), 0, Component::Vector2Df(1.f, 1.f));
        auto &tt21 = r.emplaceComponent<Component::Transform>(text21, transform21);
        auto txt21 = Component::ui::Text("./assets/pixelated.ttf", std::to_string(port), Component::ui::Color(255, 255, 255), 25);
        auto &textcmpnt21 = r.emplaceComponent<Component::ui::Text>(text21, txt21);
    }

    void Net::onQuit()
    {
        std::exit(0); // Burk
    }
}