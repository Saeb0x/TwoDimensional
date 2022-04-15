#include "OutlineText.h"


OutlineText::OutlineText() : font(nullptr) {}
OutlineText::~OutlineText() {}

void OutlineText::loadFont(const std::string& fileName, int fontSize)
{
	font = TTF_OpenFont(fileName.c_str(), fontSize);
	if (!font) 
	{ 
		SDL_Log("Failed to load font: %s", SDL_GetError());
	}
}

void OutlineText::drawText(SDL_Renderer* Renderer, std::string text, int x, int y, int r, int g, int b)
{
	SDL_Surface* tempRenderedText;
	SDL_Color textColor;
	textColor.r = r;
	textColor.g = g;
	textColor.b = b;

	tempRenderedText = TTF_RenderText_Solid(font, text.c_str(), textColor);
	SDL_Texture* RenderedText = SDL_CreateTextureFromSurface(Renderer, tempRenderedText);
	SDL_FreeSurface(tempRenderedText);

	SDL_Rect textRect;
	textRect.x = x;
	textRect.y = y;
	SDL_QueryTexture(RenderedText, nullptr,nullptr, &textRect.w, &textRect.h);
	SDL_RenderCopy(Renderer, RenderedText, nullptr, &textRect);
}