#include "Sound.h"

Sound::Sound() : sound(nullptr) {}
Sound::~Sound() {}

void Sound::loadSound(std::string fileName)
{
	sound = Mix_LoadWAV(fileName.c_str());
	if (!sound)
	{
		SDL_Log("Failed to load sound: %s", SDL_GetError());
	}
}

int Sound::playSound(int loops)
{
	if (sound)
	{
		return Mix_PlayChannel(-1, sound, loops);
	}
}