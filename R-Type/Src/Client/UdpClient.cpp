/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** UdpClient
*/

#include "UdpClient.hpp"

namespace Network
{
    namespace UDP
    {
        UdpClient::UdpClient(const std::string &addr, short port) : _socket(_context), _serverEndpoint(asio::ip::address::from_string(addr), port)
        {
            _socket.open(asio::ip::udp::v4());
            startReceive();
            _buffer.resize(1024);
        }

        void UdpClient::startOnce()
        {
            if (_context.stopped())
                _context.restart();
            _context.poll();
        }

        bool UdpClient::poll(Packet &pkt)
        {
            if (_pktQueue.empty())
                return false;
            pkt = _pktQueue.front();
            _pktQueue.pop();
            return true;
        }

        void UdpClient::startReceive()
        {
            _socket.async_receive_from(asio::buffer(_buffer.data(), _buffer.size()), _serverEndpoint,
                                       [this](std::error_code error, std::size_t size)
                                       {
                                           if (error)
                                           {
                                               std::cerr << "Receive error" << std::endl;
                                           }
                                           else
                                           {
                                               try
                                               {
                                                   Packet pkt;
                                                   pkt << _buffer;
                                                   if (pkt._magicNumber == MAGIC_NUMBER)
                                                       _pktQueue.push(pkt);
                                                   else
                                                       std::cerr << "Ignoring packet (reason wrong magic number)" << std::endl;
                                               }
                                               catch (const std::exception &e)
                                               {
                                               }
                                           }
                                           startReceive();
                                       });
        }

        void UdpClient::write(const std::vector<byte> &data, const asio::ip::udp::endpoint &end)
        {
            write(data.data(), data.size(), end);
        }

        void UdpClient::write(const byte *data, std::size_t size, const asio::ip::udp::endpoint &end)
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

        void UdpClient::write(Network::UDP::Packet &pkt)
        {
            std::vector<std::uint8_t> buffer;
            buffer << pkt;
            write(buffer.data(), buffer.size(), _serverEndpoint);
        }
    }
}