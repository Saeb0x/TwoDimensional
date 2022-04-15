#pragma once
#include "spriteComponent.h"
#include <vector>
#include "MathForGames.h"

// For the use of scrolling backgrounds
class BGSpriteComponent : public spriteComponent
{
public:
	// since this is a background and has to be drawn furthur back, it must have the lowest draw order
	BGSpriteComponent(class Actor* owner, int drawOrder = 10);
	
	void update(float DeltaTime) override;
	void draw(SDL_Renderer* Renderer) override;
	// textures used for the scrolling background
	void SetBGTextures(const std::vector<SDL_Texture*>& textures);

	void SetScreenSize(const Vector2D& size) { screenSize = size; }
	void SetScrollSpeed(float speed) { scrollSpeed = speed; }
	float GetScrollSpeed() const { return scrollSpeed; }

private:
	// encapsulation for each Background image and its own offset
	struct BGTexture
	{
		SDL_Texture* Texture;
		Vector2D offset;
	};
	std::vector<BGTexture> vBGTextures;
	Vector2D screenSize;
	float scrollSpeed;
};