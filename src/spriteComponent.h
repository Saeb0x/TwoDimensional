#pragma once
#include "Component.h"
#include "SDL.h"

class spriteComponent : public Component
{
public:
	spriteComponent(class Actor* owner, int drawOrder = 100);
	~spriteComponent();

	virtual void draw(SDL_Renderer* Renderer);
	virtual void setTexture(SDL_Texture* texture);

	int getDrawOrder() const { return DrawOrder; }
	int getTextureWidth() const { return textureWidth; }
	int getTextureHeight() const { return textureHeight; }
protected:
	SDL_Texture* Texture;
	int DrawOrder;
	int textureWidth;
	int textureHeight;
};
