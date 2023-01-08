/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** TcpClient
*/

#ifndef TCPCLIENT_HPP_
#define TCPCLIENT_HPP_
#include <asio.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include "Packet.hpp"

namespace Network
{
    namespace TCP
    {
        class TcpClient
        {
        public:
            TcpClient(const std::string &adress, short port);
            ~TcpClient();
            void write(Network::TCP::Packet &pkt);
            asio::io_context &getContext();
            bool poll(Packet &pkt);
            bool isConnected() const;
            void connect();
        protected:
            void listen()
            {
                _socket.async_read_some(asio::buffer(_buffer.data(), _buffer.size()),
                                        [this](std::error_code error, std::size_t size)
                                        {
                                            if (error)
                                                _connected = false;
                                            else if (size != 0)
                                            {
                                                try
                                                {
                                                    Packet pkt;
                                                    pkt << _buffer;
                                                    if (pkt._magicNumber == MAGIC_NUMBER)
                                                        _pktQueue.push(pkt);
                                                }
                                                catch (const std::exception &e)
                                                {
                                                    std::cerr << e.what() << '\n';
                                                }
                                            }
                                            listen();
                                        });
            }

        private:
            asio::io_context _context;
            asio::ip::tcp::socket _socket;
            std::vector<std::uint8_t> _buffer;
            std::queue<Packet> _pktQueue;
            bool _connected;
            short _port;
            std::string _addr;
        };
    }
}
#endif /* !TCPCLIENT_HPP_ */
