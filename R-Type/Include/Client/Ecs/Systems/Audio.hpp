/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** Audio
*/

#ifndef AUDIO_HPP_
#define AUDIO_HPP_

#include "ISystem.hpp"
#include "SfmlAudio.hpp"
#include <memory>
#include <SFML/Audio.hpp>
#include <unordered_map>

namespace System
{
    class Audio : public ISystem {
        public:
            Audio();
            ~Audio() = default;

        void update(float deltaTime, Registry &r);
        void stepUpdate(float deltaTime, Registry &r);

        private:
            std::unique_ptr<IAudio> _audioLib;
            std::unordered_map<std::string, std::unique_ptr<sf::Music>> _musics;
    };
}

#endif /* !AUDIO_HPP_ */
