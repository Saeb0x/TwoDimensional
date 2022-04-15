#pragma once
#include <SDL.h>
#include <unordered_map>
#include <string>
#include <vector>
#include "Graphics.h"
#include "OutlineText.h"
#include "Sound.h"


class Game
{
public:
	Game();
	bool initialization();
	void gameLoop();
	void shutDown();

	void addActor(class Actor* actor);
	void removeActor(class Actor* actor);

	void addSprite(class spriteComponent* sprite);
	void removeSprite(class spriteComponent* sprite);

	SDL_Texture* getTexture(const std::string& fileName);
private:
	void processInputs();
	void updateGame();
	void generateOutput();
	void loadData();
	void unloadData();

	SDL_Window* Window;
	SDL_Renderer* Renderer; 
	Uint32 TicksCount;
	bool EngineIsRunning;

	// map of loaded textures
	std::unordered_map<std::string, SDL_Texture*> mTextures;
	
	// all actors that exist in the game
	std::vector<class Actor*> vActors;
	// pending actors
	std::vector<class Actor*> vPendingActors;
	// to keep track of updating actors
	bool UpdatingActors;

	// all sprite components
	std::vector<class spriteComponent*> vSprites;

	// Game specific
	// ...

	// Engine's Intro
	Graphics BG;
	OutlineText TwoDimensional;
};
