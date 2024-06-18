#pragma once
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

class Sound
{
private:
    sf::SoundBuffer buffer;
    sf::Sound sound;
    sf::Music music;

public:
    Sound();
    ~Sound();

    void PlaySound(const std::string &soundpath);
    void PlayMusic(const std::string &musicpath);

    void StopMusic();
    void StopSound();

    void musicVolume(float volume);
};

Sound::Sound()
{
}

Sound::~Sound()
{
}

void Sound::PlaySound(const std::string &soundpath)
{
    if (buffer.loadFromFile(soundpath))
    {
        sound.setBuffer(buffer);
        sound.play();
    }
    else
    {
        std::cout << "Failed to load sound: " << soundpath << std::endl;
    }
}

void Sound::PlayMusic(const std::string &musicpath)
{
    if (music.openFromFile(musicpath))
    {
        music.play();
    }
    else
    {
        std::cout << "Failed to load music: " << musicpath << std::endl;
    }
}

void Sound::StopMusic()
{
    music.stop();
}

void Sound::StopSound()
{
    sound.stop();
}

void Sound::musicVolume(float volume)
{
    music.setVolume(volume);
}