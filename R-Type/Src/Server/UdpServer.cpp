/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** UdpServer
*/

#include "UdpServer.hpp"

namespace Network
{
    namespace UDP
    {
        Server::Server(short port) : _socket(_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), port)), _port(port)
        {
            startReceive();
            _data.resize(1024);
        }

        void Server::start()
        {
        }
        void Server::startOnce()
        {
            if (_context.stopped())
                _context.restart();
            _context.poll();
        }
        void Server::stop()
        {
            _context.stop();
        }
        void Server::disconnect(std::size_t id) {}

        bool Server::poll(Packet &pkt)
        {
            if (_pktQueue.empty())
                return false;
            pkt = _pktQueue.front();
            _pktQueue.pop();
            return true;
        }

        void Server::startReceive()
        {
            _socket.async_receive_from(asio::buffer(_data.data(), _data.size()), _endpoint,
                                        [this](std::error_code error, std::size_t size)
                                        {
                                            if (error)
                                            {
                                                std::cerr << "Receive error" << std::endl;
                                            }
                                            else
                                            {
                                                auto it = std::find_if(_players.begin(), _players.end(), [this](Network::UDP::Session session)
                                                                        { return session.endpoint == _endpoint; });
                                                if (it == _players.end() && _players.size() < 4)
                                                {
                                                    std::cout << "[GAME SESSION " << _port << "] New connection from : " << _endpoint.address().to_string() << std::endl;
                                                    Session session;
                                                    session.connected = true;
                                                    session.endpoint = _endpoint;
                                                    _players.emplace_back(session);
                                                }
                                                else if (it == _players.end() && _players.size() == 4)
                                                {
                                                    startReceive();
                                                    return;
                                                }
                                                else
                                                {
                                                    try
                                                    {
                                                        Packet pkt;
                                                        pkt << _data;
                                                        if (pkt._packetId < it->pktId)
                                                            return;
                                                        it->pktId = pkt._packetId;
                                                        for (std::size_t i = 0; i < _players.size(); i++)
                                                        {
                                                            if (_players[i].endpoint == _endpoint)
                                                            {
                                                                pkt._senderId = i;
                                                                break;
                                                            }
                                                        }
                                                        if (pkt._magicNumber == MAGIC_NUMBER)
                                                            _pktQueue.push(pkt);
                                                    }
                                                    catch (const std::exception &e)
                                                    {
                                                        std::cout << e.what() << std::endl;
                                                    }
                                                }
                                            }
                                            startReceive();
                                        });
        }

        void Server::write(const std::vector<byte> &data, const asio::ip::udp::endpoint &end)
        {
            write(data.data(), data.size(), end);
        }

        void Server::writeAll(const Network::UDP::Packet &pkt)
        {
            try
            {
                std::vector<byte> buffer;
                buffer << pkt;
                for (auto &client : _players)
                {
                    write(buffer, client.endpoint);
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }

        void Server::write(const byte *data, std::size_t size, const asio::ip::udp::endpoint &end)
        {
            _socket.async_send_to(asio::buffer(data, size), end,
                                    [this](std::error_code error, std::size_t /*length*/)
                                    {
                                        if (error)
                                        {
                                            std::cerr << "startWrite error" << std::endl;
                                        }
                                    });
        }
    }
};