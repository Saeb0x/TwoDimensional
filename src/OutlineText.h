#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class OutlineText
{
public:
	OutlineText();
	~OutlineText();

	void loadFont(const std::string& fileName, int fontSize);
	void drawText(SDL_Renderer* Renderer, std::string text, int x, int y, int r, int g, int b);
private:
	TTF_Font* font;
};