/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** SfmlAudio
*/

#include "SfmlAudio.hpp"
#include <iostream>

SfmlAudio::SfmlAudio()
{
}

SfmlAudio::~SfmlAudio()
{
}

void SfmlAudio::playSound(const Component::AudioSource &sound)
{
    auto it = _sounds.find(sound._filePath);
    if (it != _sounds.end())
    {
        it->second->play();
        return;
    }
    _buffer[sound._filePath] = std::make_unique<sf::SoundBuffer>();
    if (!_buffer[sound._filePath]->loadFromFile(sound._filePath)) {
        std::cerr<<"open error" << std::endl;
        return;
    }

    _sounds[sound._filePath] = std::make_unique<sf::Sound>();
    _sounds[sound._filePath]->setBuffer(*_buffer[sound._filePath]);
    _sounds[sound._filePath]->play();
}

void SfmlAudio::playMusic(const Component::AudioSource &music)
{
    auto it = _musics.find(music._filePath);
    if (it != _musics.end())
    {
        it->second->play();
        return;
    }
    _musics[music._filePath] = std::make_unique<sf::Music>();
    if (!_musics[music._filePath]->openFromFile(music._filePath))
        std::cerr<<"open error" << std::endl;
    _musics[music._filePath]->setLoop(true);
    _musics[music._filePath]->play();
   // _musics.emplace(music.filePath, musics);
}