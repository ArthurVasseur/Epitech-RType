/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** Packet
*/

#include "Packet.hpp"

Network::TCP::Packet &operator<<(Network::TCP::Packet &pkt, const std::vector<std::uint8_t> &data)
{
    if (data.size() < PACKET_TCP_SIZE)
        throw std::runtime_error("Unknown packet");
    std::size_t totalWrite = 0;
    std::memcpy(&pkt._magicNumber, data.data(), sizeof(std::uint32_t));
    totalWrite += sizeof(std::uint32_t);
    if (pkt._magicNumber != 0x424242)
        throw std::runtime_error("Unknown packet");
    std::memcpy(&pkt._commandId, data.data() + totalWrite, sizeof(std::uint32_t));
    totalWrite += sizeof(std::uint32_t);
    std::memcpy(&pkt._packetSize, data.data() + totalWrite, sizeof(std::uint32_t));
    totalWrite += sizeof(std::uint32_t);
    pkt._data.resize(pkt._packetSize);
    std::memcpy(pkt._data.data(), data.data() + totalWrite, pkt._data.size());
    return pkt;
}

std::vector<std::uint8_t> &operator<<(std::vector<std::uint8_t> &data, const Network::TCP::Packet &pkt)
{
    std::size_t totalWrite = 0;
    data.resize(PACKET_TCP_SIZE + pkt._data.size());
    std::memcpy(data.data(), &pkt._magicNumber, sizeof(std::uint32_t));
    totalWrite += sizeof(std::uint32_t);
    std::memcpy(data.data() + totalWrite, &pkt._commandId, sizeof(std::uint32_t));
    totalWrite += sizeof(std::uint32_t);
    std::memcpy(data.data() + totalWrite, &pkt._packetSize, sizeof(std::uint32_t));
    totalWrite += sizeof(std::uint32_t);
    std::memcpy(data.data() + totalWrite, pkt._data.data(), pkt._data.size());
    return data;
}

Network::UDP::Packet &operator<<(Network::UDP::Packet &pkt, const std::vector<std::uint8_t> &data)
{
    if (data.size() < PACKET_TCP_SIZE)
        throw std::runtime_error("Unknown packet");
    std::size_t totalWrite = 0;
    std::memcpy(&pkt._magicNumber, data.data(), sizeof(std::uint32_t));
    totalWrite += sizeof(std::uint32_t);
    if (pkt._magicNumber != 0x424242)
        throw std::runtime_error("Unknown packet");
    std::memcpy(&pkt._packetId, data.data() + totalWrite, sizeof(std::uint32_t));
    totalWrite += sizeof(std::uint32_t);
    std::memcpy(&pkt._commandId, data.data() + totalWrite, sizeof(std::uint32_t));
    totalWrite += sizeof(std::uint32_t);
    std::memcpy(&pkt._packetSize, data.data() + totalWrite, sizeof(std::uint32_t));
    totalWrite += sizeof(std::uint32_t);
    std::memcpy(&pkt._senderId, data.data() + totalWrite, sizeof(std::uint8_t));
    totalWrite += sizeof(std::uint8_t);
    pkt._data.resize(pkt._packetSize);
    std::memcpy(pkt._data.data(), data.data() + totalWrite, pkt._data.size());
    return pkt;
}

std::vector<std::uint8_t> &operator<<(std::vector<std::uint8_t> &data, const Network::UDP::Packet &pkt)
{
    std::size_t totalWrite = 0;
    data.resize(PACKET_UDP_SIZE + pkt._data.size());
    std::memcpy(data.data(), &pkt._magicNumber, sizeof(std::uint32_t));
    totalWrite += sizeof(std::uint32_t);
    std::memcpy(data.data() + totalWrite, &pkt._packetId, sizeof(std::uint32_t));
    totalWrite += sizeof(std::uint32_t);
    std::memcpy(data.data() + totalWrite, &pkt._commandId, sizeof(std::uint32_t));
    totalWrite += sizeof(std::uint32_t);
    std::memcpy(data.data() + totalWrite, &pkt._packetSize, sizeof(std::uint32_t));
    totalWrite += sizeof(std::uint32_t);
    std::memcpy(data.data() + totalWrite, &pkt._senderId, sizeof(std::uint32_t));
    totalWrite += sizeof(std::uint8_t);
    std::memcpy(data.data() + totalWrite, pkt._data.data(), pkt._data.size());
    return data;
};

Network::Message &operator<<(Network::Message &pkt, const std::vector<std::uint8_t> &data)
{
    if (data.size() < (2 * sizeof(std::uint32_t)))
        throw std::runtime_error("Message not standardized");
    std::size_t totalWrite = 0;
    std::memcpy(&pkt._sender._stringSize, data.data(), sizeof(std::uint32_t));
    totalWrite += sizeof(std::uint32_t);
    pkt._sender._data.resize(pkt._sender._stringSize);
    std::memcpy(pkt._sender._data.data(), data.data() + totalWrite, pkt._sender._stringSize);
    totalWrite += pkt._sender._stringSize;
    std::memcpy(&pkt._message._stringSize, data.data() + totalWrite, sizeof(std::uint32_t));
    totalWrite += sizeof(std::uint32_t);
    pkt._message._data.resize(pkt._message._stringSize);
    std::memcpy(pkt._message._data.data(), data.data() + totalWrite, pkt._message._stringSize);
    totalWrite += pkt._message._stringSize;
    return (pkt);
}

std::vector<std::uint8_t> &operator<<(std::vector<std::uint8_t> &data, const Network::Message &pkt)
{
    data.resize((2 * sizeof(std::uint32_t)) + pkt._sender._data.size() + pkt._message._data.size());
    std::size_t totalWrite = 0;
    std::memcpy(data.data() + totalWrite, &pkt._sender._stringSize, sizeof(std::uint32_t));
    totalWrite += sizeof(std::uint32_t);
    std::memcpy(data.data() + totalWrite, pkt._sender._data.data(), pkt._sender._data.size());
    totalWrite += pkt._sender._stringSize;
    std::memcpy(data.data() + totalWrite, &pkt._message._stringSize, sizeof(std::uint32_t));
    totalWrite += sizeof(std::uint32_t);
    std::memcpy(data.data() + totalWrite, pkt._message._data.data(), pkt._message._data.size());
    return data;
}

Network::String &operator<<(Network::String &pkt, const std::vector<std::uint8_t> &data)
{
    std::size_t totalWrite = 0;
    if (data.size() < (sizeof(std::uint32_t)))
        throw std::runtime_error("String not standardized");
    std::memcpy(&pkt._stringSize, data.data(), sizeof(std::uint32_t));
    totalWrite += sizeof(std::uint32_t);
    pkt._data.resize(pkt._stringSize);
    std::memcpy(pkt._data.data(), data.data() + totalWrite, pkt._stringSize);
    return pkt;
}

std::vector<std::uint8_t> &operator<<(std::vector<std::uint8_t> &data, const Network::String &pkt)
{
    std::size_t totalWrite = 0;
    data.resize(pkt._stringSize + sizeof(std::uint32_t));
    std::memcpy(data.data(), &pkt._stringSize, sizeof(std::uint32_t));
    totalWrite += sizeof(std::uint32_t);
    std::memcpy(data.data() + totalWrite, pkt._data.data(), pkt._stringSize);
    return data;
}

Network::Port &operator<<(Network::Port &pkt, const std::vector<std::uint8_t> &data)
{
    std::size_t totalWrite = 0;
    if (data.size() != (sizeof(std::int16_t)))
        throw std::runtime_error("Unexpected size of Port");
    std::memcpy(&pkt._port, data.data(), sizeof(std::int16_t));
    return pkt;
}

std::vector<std::uint8_t> &operator<<(std::vector<std::uint8_t> &data, const Network::Port &pkt)
{
    std::size_t totalWrite = 0;
    data.resize(sizeof(std::int16_t));
    std::memcpy(data.data(), &pkt._port, sizeof(std::uint32_t));
    return data;
}

Network::UDP::NetworkedComponent &operator<<(Network::UDP::NetworkedComponent &pkt, const std::vector<std::uint8_t> &data)
{
    std::size_t totalRead = 0;
    std::memcpy(&pkt._id, data.data(), sizeof(std::uint32_t));
    totalRead += sizeof(std::uint32_t);
    std::memcpy(&pkt._dataSize, data.data() + totalRead, sizeof(std::uint32_t));
    totalRead += sizeof(std::uint32_t);
    if (pkt._dataSize > 0)
    {
        pkt._data.resize(pkt._dataSize);
        std::memcpy(pkt._data.data(), data.data() + totalRead, pkt._dataSize);
    }
    return (pkt);
}

std::vector<std::uint8_t> &operator<<(std::vector<std::uint8_t> &data, const Network::UDP::NetworkedComponent &pkt)
{
    std::size_t totalWrite = 0;
    data.resize(NETWORKED_COMPONENT_SIZE + pkt._dataSize);
    std::memcpy(data.data(), &pkt._id, sizeof(std::uint32_t));
    totalWrite += sizeof(std::uint32_t);
    std::memcpy(data.data() + totalWrite, &pkt._dataSize, sizeof(std::uint32_t));
    totalWrite += sizeof(std::uint32_t);
    std::memcpy(data.data() + totalWrite, pkt._data.data(), pkt._dataSize);
    return (data);
}