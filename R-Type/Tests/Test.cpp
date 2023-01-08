/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** Test
*/

#include <gtest/gtest.h>
#include <iostream>
#include "Packet.hpp"

TEST(Packet, Message)
{
    Network::Message msg("sender", "message");
    Network::TCP::Packet pkt(0x424242, 1002, msg);
    Network::TCP::Packet pkt2;
    Network::Message msg2;

    std::vector<std::uint8_t> vec;
    vec << pkt;
    pkt2 << vec;
    msg2 << pkt2._data;

    EXPECT_EQ(0x424242, pkt2._magicNumber);
    EXPECT_EQ(1002, pkt2._commandId);
    EXPECT_EQ(pkt2._data.size(), pkt2._packetSize);
    EXPECT_EQ(std::string("sender"), std::string((char *)msg2._sender._data.data()));
    EXPECT_EQ(std::string("message"), std::string((char *)msg2._message._data.data()));
}

TEST(Packet, String)
{
    Network::String str("Hello World !");
    Network::TCP::Packet pkt(0x424242, 1001, str);
    Network::TCP::Packet pkt2;
    Network::String str2;

    std::vector<std::uint8_t> vec;
    vec << pkt;
    pkt2 << vec;
    str2 << pkt2._data;

    EXPECT_EQ(0x424242, pkt2._magicNumber);
    EXPECT_EQ(1001, pkt2._commandId);
    EXPECT_EQ(pkt2._data.size(), pkt._data.size());
    EXPECT_EQ(std::string("Hello World !"), std::string((char *)str2._data.data()));
}

TEST(Array, test)
{
    SUCCEED();
}
