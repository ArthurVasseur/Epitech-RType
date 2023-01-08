/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** TcpClient
*/

#include "TcpClient.hpp"

namespace Network
{
    namespace TCP
    {
        TcpClient::TcpClient(const std::string &address, short port) : _socket(_context), _connected(true), _addr(address), _port(port)
        {
            connect();
        }

        TcpClient::~TcpClient()
            {
                _socket.close();
            }

        void TcpClient::connect()
        {
            auto ep = asio::ip::tcp::endpoint(asio::ip::address::from_string(_addr), _port);
            _buffer.resize(512);
            try
            {
                _socket.connect(ep);
                _connected = true;
            }
            catch(const std::exception& e)
            {
                _connected = false;
                return;
            }
            listen();
        }

        void TcpClient::write(Network::TCP::Packet &pkt)
        {
            std::vector<std::uint8_t> buffer;
            buffer << pkt;
            asio::async_write(_socket, asio::buffer(buffer.data(), buffer.size()),
                                     [this](asio::error_code error, std::size_t /*length*/)
                                     {
                                         if (error)
                                         {
                                             std::cerr << "Write error" << std::endl;
                                         }
                                     });
        }
        asio::io_context &TcpClient::getContext()
        {
            return _context;
        }

        bool TcpClient::poll(Packet &pkt)
        {
            if (_pktQueue.empty())
                return false;
            pkt = _pktQueue.front();
            _pktQueue.pop();
            return true;
        }
        bool TcpClient::isConnected() const
        {
            return _connected;
        }
    }
}
