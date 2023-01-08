/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** AudioSource
*/

#ifndef AUDIOSOURCE_HPP_
#define AUDIOSOURCE_HPP_

#include <string>

namespace Component {
    struct AudioSource
    {

        enum Type {
            MUSIC,
            SOUND
        };
        AudioSource(std::string filePath, bool play, bool loop, Type type) : _filePath(filePath), _play(play), _loop(loop), _type(type){}
        std::string _filePath;
        bool _play;
        bool _loop;
        Type _type;
    };
}

#endif /* !AUDIOSOURCE_HPP_ */
