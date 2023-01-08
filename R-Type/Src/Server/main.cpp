/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** main
*/

#include <chrono>
#include <thread>
#include "Server.hpp"
#include "World.hpp"
#include "Registry.hpp"
#include "GameLobby.hpp"
#include "UdpServer.hpp"
short GameLobby::_maxPort = 2150;

int main(int argc, const char *argv[])
{
    asio::io_context io;
    std::vector<std::thread> threads;
    std::shared_ptr<Network::TCP::Server> serv(new Network::TCP::Server(
        "MAIN SERVER", [&threads](Network::TCP::Packet pkt, Network::TCP::Socket &sock)
        {
            if (pkt._magicNumber != MAGIC_NUMBER)
                return;
            switch ((Network::TCP::Command::Client)pkt._commandId)
            {
            case Network::TCP::Command::Client::CreateLobby:
                threads.push_back(std::thread([&sock, &threads]()
                                              {
                                                  GameLobby lobby(threads);
                                                  auto command = (std::uint32_t)Network::TCP::Command::Server::LobbyPort;
                                                  Network::Port port(lobby.getPort());
                                                  Network::TCP::Packet pkt(MAGIC_NUMBER, command, port);
                                                  sock.write(pkt);
                                                  lobby.run();
                                              }));
                break;
            default:
                break;
            }
        },
        io, 2121));

    while (true)
    {
        if (io.stopped())
            io.restart();
        io.poll();
        serv->removeDisconectedSockets();
    }
    // Network::UDP::Server serv(2121);
    // serv.start();
    return 0;
}
