/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** IAudio
*/

#ifndef IAUDIO_HPP_
#define IAUDIO_HPP_

#include "AudioSource.hpp"

class IAudio {
    public:
        virtual void playSound(const Component::AudioSource &sound) = 0;

        virtual void playMusic(const Component::AudioSource &music) = 0;

        ~IAudio() = default;
};

#endif /* !IAUDIO_HPP_ */
