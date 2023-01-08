/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** Packet
*/

#ifndef PACKET_HPP_
#define PACKET_HPP_

#include <string>
#include <cstring>
#include <vector>
#include <stdexcept>
#include "Transform.hpp"
#define PACKET_TCP_SIZE 3 * sizeof(std::uint32_t)
#define PACKET_UDP_SIZE 4 * sizeof(std::uint32_t)
#define NETWORKED_COMPONENT_SIZE 3 * sizeof(std::uint32_t)
#define MAGIC_NUMBER 0x424242

namespace Network
{
    using byte = std::uint8_t;
    namespace TCP
    {
        namespace Command
        {
            enum class Client : std::uint32_t
            {
                SignIn = 1001,
                SendMessage = 1002,
                StartGame = 1003,
                CreateLobby = 1004,
                JoinLobby = 1005,
            };
            enum class Server : std::uint32_t
            {
                PlayerConnect = 2001,
                PlayerDisconnect = 2002,
                PlayerColor = 2003,
                Message = 2004,
                StartingGame = 2005,
                LobbyPort = 2006,
            };
        }

        struct Packet
        {
            Packet() : _magicNumber(0), _commandId(0), _packetSize(0) {}
            template <typename T>
            Packet(std::uint32_t magicNumber, std::uint32_t commandId, const T &data) : _magicNumber(magicNumber), _commandId(commandId)
            {
                _data << data;
                _packetSize = _data.size();
            }
            Packet(std::uint32_t magicNumber, std::uint32_t commandId) : _magicNumber(magicNumber), _commandId(commandId)
            {
                _packetSize = 0;
            }
            std::uint32_t _magicNumber;
            std::uint32_t _commandId;
            std::uint32_t _packetSize;
            std::vector<std::uint8_t> _data;
        };

        struct Lobby
        {
            Lobby() : _numberOfPlayers(0) {}
            Lobby(const std::string &lobbyName, std::uint32_t numberOfPlayers) : _lobbyName(lobbyName), _numberOfPlayers(numberOfPlayers) {}

            std::string _lobbyName;
            std::uint32_t _numberOfPlayers;
        };
    } // namespace TCP

    namespace UDP
    {
        enum class Command : std::uint32_t
        {
            PlayerR = 3001,
            PlayerG = 3002,
            PlayerY = 3003,
            PlayerB = 3004,
            PlayerShot = 3005,
            Enemy = 3006,
            EnemyShot = 3007,
            Disconected = 3008,
            Dead = 3009,
            Input = 3010
        };
        struct Packet
        {
            Packet() : _magicNumber(0), _commandId(0), _packetSize(0), _packetId(0), _senderId(0) {}
            template <typename T>
            Packet(std::uint32_t magicNumber, std::uint32_t commandId, std::uint32_t packetId, const T &data) : _magicNumber(magicNumber), _commandId(commandId), _packetId(packetId), _senderId(0)
            {
                _data << data;
                _packetSize = _data.size();
            }
            Packet(std::uint32_t magicNumber, std::uint32_t commandId, std::uint32_t packetId) : _magicNumber(magicNumber), _commandId(commandId), _packetId(packetId), _senderId(0)
            {
                _packetSize = 0;
            }
            std::uint32_t _magicNumber;
            std::uint32_t _packetId;
            std::uint32_t _commandId;
            std::uint32_t _packetSize;
            std::uint8_t _senderId;
            std::vector<std::uint8_t> _data;
        };

        struct NetworkedComponent
        {
            NetworkedComponent() : _id(0) {}
            template <typename T>
            NetworkedComponent(std::uint32_t id, const T &comp) : _id(id)
            {
                _data.resize(sizeof(T));
                _dataSize = sizeof(T);
                std::memcpy(_data.data(), &comp, _dataSize);
            }
            std::uint32_t _id;
            std::uint32_t _dataSize;
            std::vector<byte> _data;
        };
    } // namespace UDP
    struct String
    {
        String() {}
        String(const std::string &str) : _stringSize(str.size())
        {
            _data.resize(str.size());
            std::memcpy(_data.data(), str.data(), _stringSize);
        }
        std::uint32_t _stringSize;
        std::vector<std::uint8_t> _data;
    };

    struct Message
    {
        Message() {}
        Message(const std::string &sender, const std::string &message) : _sender(sender), _message(message) {}
        String _sender;
        String _message;
    };

    struct Port
    {
        Port() {}
        Port(std::int16_t port) : _port(port) {}
        std::int16_t _port;
    };
} // namespace Network

Network::TCP::Packet &operator<<(Network::TCP::Packet &pkt, const std::vector<std::uint8_t> &data);
std::vector<std::uint8_t> &operator<<(std::vector<std::uint8_t> &data, const Network::TCP::Packet &pkt);
Network::UDP::Packet &operator<<(Network::UDP::Packet &pkt, const std::vector<std::uint8_t> &data);
std::vector<std::uint8_t> &operator<<(std::vector<std::uint8_t> &data, const Network::UDP::Packet &pkt);
Network::Message &operator<<(Network::Message &pkt, const std::vector<std::uint8_t> &data);
std::vector<std::uint8_t> &operator<<(std::vector<std::uint8_t> &data, const Network::Message &pkt);
Network::String &operator<<(Network::String &pkt, const std::vector<std::uint8_t> &data);
std::vector<std::uint8_t> &operator<<(std::vector<std::uint8_t> &data, const Network::String &pkt);
Network::Port &operator<<(Network::Port &pkt, const std::vector<std::uint8_t> &data);
std::vector<std::uint8_t> &operator<<(std::vector<std::uint8_t> &data, const Network::Port &pkt);

Network::UDP::NetworkedComponent &operator<<(Network::UDP::NetworkedComponent &pkt, const std::vector<std::uint8_t> &data);
std::vector<std::uint8_t> &operator<<(std::vector<std::uint8_t> &data, const Network::UDP::NetworkedComponent &pkt);
#endif /* !PACKET_HPP_ */
