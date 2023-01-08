/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_
#include <memory>
#include <iostream>
#include <map>
#include "IServer.hpp"
namespace Network
{
    namespace TCP
    {
        class Socket final : public ISocket
        {
        public:
            Socket(std::size_t id, std::function<void(Packet &, Socket &)> callblack, asio::ip::tcp::socket socket, const std::string &name) ;
            ~Socket();
            void write(const Packet &pkt) override;

            void close() override;
            std::size_t getId() const override;

            bool disconected() const final;

        protected:
            void onRead();
            asio::ip::tcp::socket _socket;
            std::vector<std::uint8_t> _buffer;
            std::function<void(Packet &, Socket &)> _callblack;
            std::size_t _id;
            bool _disconnected;
            bool _isConnected;
            std::string _name;
        };

        class Server final : public IServer
        {
        public:
            Server(const std::string &name, std::function<void(Packet &, Socket &)> callblack, asio::io_context &io, short port);
            ~Server() = default;

            void start() override;
            void stop() override;
            void disconnect(std::size_t id) override;
            void removeDisconectedSockets();
            std::map<std::shared_ptr<ISocket>, bool> getSessions();

        private:
            void startAccept(std::function<void(Packet &, Socket &)> callblack);
            void sendConnectedClients();
            asio::io_context &_context;
            asio::ip::tcp::acceptor _acceptor;
            std::map<std::shared_ptr<ISocket>, bool> _sockets;
            std::size_t _maxId;
            std::string _name;
        };
    }
}

#endif /* !SERVER_HPP_ */
