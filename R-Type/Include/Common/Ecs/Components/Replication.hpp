/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** Replication
*/

#ifndef REPLICATION_HPP_
#define REPLICATION_HPP_
#include <chrono>
namespace Component
{
    struct Replication
    {
        Replication(bool r, std::uint32_t id) : replicates(r), _id(id), _lastUpdate(std::chrono::steady_clock::now()) {}
        bool replicates;
        std::uint32_t _id;
        std::chrono::steady_clock::time_point _lastUpdate;
    };
}

#endif /* !REPLICATION_HPP_ */
