/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** SfmlAudio
*/

#ifndef SFMLAUDIO_HPP_
#define SFMLAUDIO_HPP_

#include "IAudio.hpp"
#include <SFML/Audio.hpp>
#include <unordered_map>

class SfmlAudio : public IAudio {
    public:
        SfmlAudio();
        ~SfmlAudio();

    void playSound(const Component::AudioSource &sound) final;

    void playMusic(const Component::AudioSource &music) final;

    private:
        std::unordered_map<std::string, std::unique_ptr<sf::Music>> _musics;
        std::unordered_map<std::string, std::unique_ptr<sf::Sound>> _sounds;
        std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>> _buffer;

};

#endif /* !SFMLAUDIO_HPP_ */
