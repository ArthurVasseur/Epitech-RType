/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** Tag
*/

#ifndef TAG_HPP_
#define TAG_HPP_
#include <string>

namespace Component
{
    struct Tag
    {
        Tag(const std::string &tag) : name(tag){}
        std::string name;
    };
}
#endif /* !TAG_HPP_ */
