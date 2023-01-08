/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** GameLobby
*/

#ifndef GAMELOBBY_HPP_
#define GAMELOBBY_HPP_
#include "Server.hpp"
#include "GameSession.hpp"
class GameLobby
{
public:
    //To do : destroy if no one has logged in for X sesconds
    GameLobby(std::vector<std::thread> &threads);
    ~GameLobby() = default;

    void onNewData(Network::TCP::Packet &pkt, Network::TCP::Socket &sock);
    void run();
    short getPort() const;

protected:
private:
    static short _maxPort;
    short _port;
    asio::io_context _context;
    Network::TCP::Server _server;
    std::vector<std::thread> &_threads;
};

#endif /* !GAMELOBBY_HPP_ */
