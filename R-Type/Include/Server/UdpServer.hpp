/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** UdpServer
*/

#ifndef UDPSERVER_HPP_
#define UDPSERVER_HPP_
#include <iostream>
#include <array>
#include <queue>
#include <algorithm>
#include "IServer.hpp"
#include "asio.hpp"
namespace Network
{
    namespace UDP
    {

        struct Session
        {
            Session() : pktId(0), connected(true) {}
            asio::ip::udp::endpoint endpoint;
            std::uint32_t pktId;
            bool connected;
        };

        class Server : public IServer
        {
        public:
            Server(short port);

            ~Server() = default;
            void start();
            void startOnce();
            void stop();
            void disconnect(std::size_t id);

            bool poll(Packet &pkt);
            void startReceive();
            void write(const std::vector<byte> &data, const asio::ip::udp::endpoint &end);

            void writeAll(const Network::UDP::Packet &pkt);

            void write(const byte *data, std::size_t size, const asio::ip::udp::endpoint &end);

        protected:
        private:
            asio::io_context _context;
            asio::ip::udp::socket _socket;
            std::vector<byte> _data;
            asio::ip::udp::endpoint _endpoint;
            std::vector<Session> _players;
            short _port;
            std::queue<Packet> _pktQueue;
        };
    }
};

#endif /* !UDPSERVER_HPP_ */
