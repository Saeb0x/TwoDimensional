#include "Game.h"
#include "Actor.h"
#include "spriteComponent.h"
#include "BGspriteComponent.h"
#include <algorithm>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

Game::Game() : Window(nullptr), Renderer(nullptr), EngineIsRunning(true), UpdatingActors(false), TicksCount(0) {}

bool Game::initialization()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Failed to initialize SDL subsystems: %s", SDL_GetError());
		return false;
	}

	Window = SDL_CreateWindow("TwoDimensional", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, 0);
	if (!Window)
	{
		SDL_Log("Failed to create a window!");
		return false;
	}

	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!Renderer)
	{
		SDL_Log("Failed to create a renderer!");
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Failed to initialize SDL image: %s", SDL_GetError());
		return false;
	}

	if (TTF_Init() != 0)
	{
		SDL_Log("Failed to initialize SDL font: %s", SDL_GetError());
		return false;
	}

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048) != 0)
	{
		SDL_Log("Failed to initialize SDL mixer: %s", SDL_GetError());
		return false;
	}

	loadData();
	
	TicksCount = SDL_GetTicks();

	return true;
}

void Game::gameLoop()
{
	while (EngineIsRunning)
	{
		processInputs();
		updateGame();
		generateOutput();
	}
}

void Game::processInputs()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			EngineIsRunning = false;
			break;
		}
	}

	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
	if (keyboardState[SDL_SCANCODE_ESCAPE])
	{
		EngineIsRunning = false;
	}

	// process input
	// ...
}

void Game::updateGame()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), TicksCount + 16)); // wait unit 16ms has elapsed since last frame (frame limiting)	
	
	float DeltaTime = (SDL_GetTicks() - TicksCount) / 1000.0f;
	if (DeltaTime > 0.05f)
	{
		DeltaTime = 0.05f;
	}
	TicksCount = SDL_GetTicks();

	// update all actors
	UpdatingActors = true;
	for (auto actor : vActors)
	{
		actor->update(DeltaTime);
	}
	UpdatingActors = false;

	// move all pending actors to actors
	for (auto pendingActor : vPendingActors)
	{
		vActors.emplace_back(pendingActor);
	}
	vPendingActors.clear();

	// move any dead actors to a temporary vector
	std::vector<Actor*> vDeadActors;
	for (auto deadActor : vActors)
	{
		if (deadActor->GetState() == Actor::State::Dead)
		{
			vDeadActors.emplace_back(deadActor);
		}
	}

	// delete dead actors
	for (auto deadActor : vDeadActors)
	{
		delete deadActor;
	}
}

void Game::generateOutput()
{
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
	// SDL_RenderClear(Renderer);
	
	// draw all sprite components
	for (auto sprite : vSprites)
	{
		sprite->draw(Renderer);
	}

	// Engine's intro
	BG.drawPixel(Renderer, rand() % 1024, rand() % 800, rand() % 255, rand() % 255, rand() % 255);
	TwoDimensional.drawText(Renderer, "TwoDimensional Engine", 150, 300, 255, 0, 0);

	SDL_RenderPresent(Renderer);
}

void Game::loadData()
{
	// load game's data
	// ...

	// Engine's intro
	TwoDimensional.loadFont("Fonts/VT323.ttf", 90);
}

void Game::unloadData()
{
	// delete actors
	while (!vActors.empty())
	{
		delete vActors.back();
	}

	// destroy textures
	for (auto key : mTextures)
	{
		SDL_DestroyTexture(key.second);
	}
	mTextures.clear();
}

void Game::shutDown()
{
	unloadData();
	Mix_CloseAudio();
	TTF_Quit();
	IMG_Quit();
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	SDL_Quit();
}

SDL_Texture* Game::getTexture(const std::string& fileName)
{
	SDL_Texture* texture = nullptr;

	// to check if the texture is in the map or not
	auto vIterator = mTextures.find(fileName);
	if (vIterator != mTextures.end())
	{
		texture = vIterator->second;
	}
	else 
	{
		SDL_Surface* tempSurface = IMG_Load(fileName.c_str());
		if (!tempSurface)
		{
			SDL_Log("Failed to load texture file: %s", fileName.c_str());
			return nullptr;
		}

		texture = SDL_CreateTextureFromSurface(Renderer, tempSurface);
		SDL_FreeSurface(tempSurface);
		if (!texture)
		{
			SDL_Log("A failure occured while converting the surface to a texture for %s", fileName.c_str());
			return nullptr;
		}

		mTextures.emplace(fileName.c_str(), texture);
	}
	return texture;
}

void Game::addActor(Actor* actor)
{
	// while updating actors, we add the current actor to pending
	if (UpdatingActors)
	{
		vPendingActors.emplace_back(actor);
	}
	else
	{
		vActors.emplace_back(actor);
	}
}

void Game::removeActor(Actor* actor)
{
	// to check if our actor is in the pending actors
	auto vIterator = std::find(vPendingActors.begin(), vPendingActors.end(), actor);
	if (vIterator != vPendingActors.end())
	{
		std::iter_swap(vIterator, vPendingActors.end() - 1);
		vPendingActors.pop_back();
	}

	// to check if our actor is in actors
	vIterator = std::find(vActors.begin(), vActors.end(), actor);
	if (vIterator != vActors.end())
	{
		std::iter_swap(vIterator, vActors.end() - 1);
		vActors.pop_back();
	}
}

void Game::addSprite(spriteComponent* sprite)
{
	// the insertion in vSprites has a priority according to the higher order
	int DrawOrder = sprite->getDrawOrder();
	auto vIterator = vSprites.begin();
	for (; vIterator != vSprites.end(); ++vIterator)
	{
		if (DrawOrder < (*vIterator)->getDrawOrder())
		{
			break;
		}
	}

	vSprites.insert(vIterator, sprite);
}

void Game::removeSprite(spriteComponent* sprite)
{
	auto vIterator = std::find(vSprites.begin(), vSprites.end(), sprite);
	vSprites.erase(vIterator);
}


