/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** ITcpServer
*/

#ifndef ITCPSERVER_HPP_
#define ITCPSERVER_HPP_
#include <asio.hpp>
#include <vector>
#include <functional>
#include "Packet.hpp"

namespace Network
{
    namespace TCP
    {
        class ISocket
        {
        public:
            virtual void write(const Packet &) = 0;
            virtual void close() = 0;
            virtual std::size_t getId() const = 0;
            virtual bool disconected() const = 0;

        private:
            virtual void onRead() = 0;
        };

    }
    class IServer
    {
    public:
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual void disconnect(std::size_t id) = 0;
    };
} // namespace Network

#endif /* !ITCPSERVER_HPP_ */
