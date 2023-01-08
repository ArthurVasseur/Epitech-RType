/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** Sprite
*/

#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include <string>

namespace Component {
    struct Sprite
    {
        Sprite(const std::string &sprite) : _path(sprite) {}
        std::string _path;
    };
}
#endif /* !SPRITE_HPP_ */
