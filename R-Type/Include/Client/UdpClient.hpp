/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** UdpClient
*/

#ifndef UDPCLIENT_HPP_
#define UDPCLIENT_HPP_
#include <asio.hpp>
#include <queue>
#include <iostream>
#include "Packet.hpp"

namespace Network
{
    namespace UDP
    {
        class UdpClient
        {
        public:
            UdpClient(const std::string &addr, short port);
            ~UdpClient() = default;

            void startOnce();
            bool poll(Packet &pkt);
            void startReceive();
            void write(const std::vector<byte> &data, const asio::ip::udp::endpoint &end);
            void write(const byte *data, std::size_t size, const asio::ip::udp::endpoint &end);
            void write(Network::UDP::Packet &pkt);

        protected:
        private:
            asio::io_context _context;
            asio::ip::udp::socket _socket;
            asio::ip::udp::endpoint _serverEndpoint;
            std::vector<std::uint8_t> _buffer;
            std::queue<Packet> _pktQueue;
        };
    }
}

#endif /* !UDPCLIENT_HPP_ */
