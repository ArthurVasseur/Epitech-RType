/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** GameLobby
*/

#include "GameLobby.hpp"

GameLobby::GameLobby(std::vector<std::thread> &threads) : _server(std::string("GAME LOBBY ") + std::to_string(_maxPort - 1), std::bind(&GameLobby::onNewData, this, std::placeholders::_1, std::placeholders::_2), _context, _maxPort++), _threads(threads)
{
    _port = _maxPort - 1;
}

void GameLobby::onNewData(Network::TCP::Packet &pkt, Network::TCP::Socket &sock)
{
    if ((Network::TCP::Command::Client)pkt._commandId == Network::TCP::Command::Client::StartGame)
    {
        auto sessions = _server.getSessions();
        auto command = (std::uint32_t)Network::TCP::Command::Server::StartingGame;
        Network::Port port(_maxPort++);
        Network::TCP::Packet pkt(MAGIC_NUMBER, command, port);
        for (auto session : sessions)
        {
            session.first->write(pkt);
        }
        _threads.push_back(std::thread([this]()
                                       {
                                               std::cout << "[GAME LOBBY " << (_maxPort - 1) << "] Create new game session" << std::endl;
                                               GameSession gs(_maxPort - 1);
                                               gs.run(); }));
    }
    if ((Network::TCP::Command::Server)pkt._commandId == Network::TCP::Command::Server::PlayerDisconnect)
    {
        auto sessions = _server.getSessions();
        for (auto session : sessions)
        {
            try
            {
                session.first->write(pkt);
            }
            catch (...)
            {
            }
        }
    }
}

void GameLobby::run()
{
    _context.run();
}

short GameLobby::getPort() const
{
    return _port;
}