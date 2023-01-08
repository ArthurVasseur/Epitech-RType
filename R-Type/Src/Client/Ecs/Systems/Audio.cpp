/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** Audio
*/

#include "Audio.hpp"

namespace System {

    Audio::Audio()
    {
        _audioLib = std::make_unique<SfmlAudio>();
    }

    void Audio::update(float deltaTime, Registry &r)
    {
        auto &audioSources = r.getComponents<Component::AudioSource>();
        for (Entity entity = 0; entity < audioSources.size(); entity++) {
            if (!r.hasComponent<Component::AudioSource>(entity))
                continue;
            auto &audioSource = r.getComponent<Component::AudioSource>(entity);
            if (audioSource._play == true) {
                if (audioSource._type == Component::AudioSource::MUSIC)
                    _audioLib->playMusic(audioSource);
                else
                    _audioLib->playSound(audioSource);
                audioSource._play = false;
            }
        }
    }

    void Audio::stepUpdate(float deltaTime, Registry &r)
    {
    }
}