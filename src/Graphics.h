#pragma once
#include <SDL.h>

// to draw primitive graphics
class Graphics
{
public:
	Graphics();
	~Graphics();
	void drawPixel(SDL_Renderer* Renderer, int x, int y, int r, int g, int b);
	void drawOutlinedRect(SDL_Renderer* Renderer, int x, int y, int width, int height, int r, int g, int b);
	void drawFilledRect(SDL_Renderer* Renderer, int x, int y, int width, int height, int r, int g, int b);
};