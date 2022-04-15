#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <string>

class Sound
{
public:
	Sound();
	~Sound();
	void loadSound(std::string fileName);
	int playSound(int loops = 0);
private:
	Mix_Chunk* sound;
};