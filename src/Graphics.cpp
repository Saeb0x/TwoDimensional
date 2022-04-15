#include "Graphics.h"

Graphics::Graphics() {}
Graphics::~Graphics() {}

void Graphics::drawPixel(SDL_Renderer* Renderer, int x, int y, int r, int g, int b)
{
	SDL_SetRenderDrawColor(Renderer, r, g, b, 255);
	SDL_RenderDrawPoint(Renderer, x, y);
}

void Graphics::drawOutlinedRect(SDL_Renderer* Renderer, int x, int y, int width, int height, int r, int g, int b)
{
	SDL_Rect outlinedRect;
	outlinedRect.x = x;
	outlinedRect.y = y;
	outlinedRect.w = width;
	outlinedRect.h = height;

	SDL_SetRenderDrawColor(Renderer, r, g, b, 255);
	SDL_RenderDrawRect(Renderer, &outlinedRect);
}

void Graphics::drawFilledRect(SDL_Renderer* Renderer, int x, int y, int width, int height, int r, int g, int b)
{
	SDL_Rect filledRect;
	filledRect.x = x;
	filledRect.y = y;
	filledRect.w = width;
	filledRect.h = height;

	SDL_SetRenderDrawColor(Renderer, r, g, b, 255);
	SDL_RenderFillRect(Renderer, &filledRect);
}