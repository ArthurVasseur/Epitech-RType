/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** Sprite
*/

#ifndef SHIP_HPP_
#define SHIP_HPP_

#include <string>
#include <chrono>

namespace Component {
    struct Ship
    {
        enum Type {Player, Enemy};
        Ship(Type type) : _type(type) {}
        Type _type;
        std::chrono::steady_clock::time_point lastShot;
    };
}
#endif /* !SHIP_HPP_ */