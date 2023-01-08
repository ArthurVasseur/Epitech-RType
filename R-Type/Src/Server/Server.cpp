/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** Server
*/

#include "Server.hpp"

namespace Network
{
    namespace TCP
    {


        Socket::Socket(std::size_t id, std::function<void(Packet &, Socket &)> callblack, asio::ip::tcp::socket socket, const std::string &name) : _id(id), _socket(std::move(socket)), _callblack(callblack), _disconnected(false), _name(name), _isConnected(false)
        {
            _buffer.resize(512);
            std::cout << '[' << name << "] New connection from " << _socket.remote_endpoint().address().to_string() << std::endl;
            onRead();
        }
        Socket::~Socket()
        {
            _socket.close();
        }

        void Socket::write(const Packet &pkt) 
        {
            if (_disconnected)
                return;
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

        void Socket::close() 
        {
            _socket.close();
        }

        std::size_t Socket::getId() const 
        {
            return _id;
        }

        bool Socket::disconected() const 
        {
            return _disconnected;
        }


        void Socket::onRead()
        {
            _socket.async_read_some(asio::buffer(_buffer.data(), _buffer.size()),
                                    [this](asio::error_code error, std::size_t length)
                                    {
                                        if (asio::error::eof == error || asio::error::connection_reset == error)
                                        {
                                            if (_name == "MAIN SERVER")
                                                return;
                                            try
                                            {
                                                std::cout << "[" << _name << "] Client " << _socket.remote_endpoint().address().to_string() << " disconected" << std::endl;
                                            }
                                            catch(const std::exception& e)
                                            {
                                                return;
                                            }
                                            _disconnected = true;
                                            Port nb(_id);
                                            Packet pkt(MAGIC_NUMBER, (std::uint32_t)Command::Server::PlayerDisconnect, nb);
                                            _callblack(pkt, *this);
                                            _isConnected = false;
                                        }
                                        else
                                        {
                                            try
                                            {
                                                Packet pkt;
                                                pkt << _buffer;
                                                _callblack(pkt, *this);
                                            }
                                            catch (const std::exception &e)
                                            {
                                                std::cerr << e.what() << '\n';
                                            }
                                        }
                                        onRead();
                                    });
        }

        Server::Server(const std::string &name, std::function<void(Packet &, Socket &)> callblack, asio::io_context &io, short port) : _context(io), _acceptor(_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)), _maxId(0), _name(name)
        {
            std::cout << '[' << name << "] running on port " << port << std::endl;
            startAccept(callblack);
        }

        void Server::start() 
        {
            _context.run();
        }

        void Server::stop() 
        {
            _context.stop();
        }

        void Server::disconnect(std::size_t id) 
        {
            for (auto &sock : _sockets)
            {
                if (sock.first->getId() == id)
                {
                    sock.second = true;
                    return;
                }
            }
        }

        void Server::removeDisconectedSockets()
        {
            for (auto it = _sockets.begin(); it != _sockets.end();)
            {
                if (it->first->disconected())
                {
                    it = _sockets.erase(it);
                }
                else
                    it++;
            }
        }

        std::map<std::shared_ptr<ISocket>, bool> Server::getSessions()
        {
            return _sockets;
        }

        void Server::startAccept(std::function<void(Packet &, Socket &)> callblack)
        {
            _acceptor.async_accept(
                [this, callblack](asio::error_code error, asio::ip::tcp::socket socket)
                {
                    if (!error)
                    {
                        auto ptr = std::shared_ptr<ISocket>(new Socket(_maxId++, callblack, std::move(socket), _name));
                        _sockets[ptr] = true;
                        if (_name != "MAIN SERVER")
                            sendConnectedClients();
                    }
                    startAccept(callblack);
                });
        }

        void Server::sendConnectedClients()
        {
            Port nb(_maxId - 1);
            Packet pkt(MAGIC_NUMBER, (std::uint32_t)Command::Server::PlayerConnect, nb);
            for (auto &session : _sockets)
                session.first->write(pkt);
            for (auto &session : _sockets)
            {
                Port nb2(session.first->getId());
                Packet pkt2(MAGIC_NUMBER, (std::uint32_t)Command::Server::PlayerConnect, nb2);
                for (auto &s : _sockets)
                {
                    using namespace std::chrono_literals;
                    std::this_thread::sleep_for(5ms);
                    s.first->write(pkt2);
                }
            }
        }
    }
}