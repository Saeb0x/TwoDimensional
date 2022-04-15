#pragma once
#include "spriteComponent.h"
#include <vector>

class animatedSpriteComponent : public spriteComponent
{
public:
	animatedSpriteComponent(class Actor* owner, int drawOrder = 100);

	// frame by frame animation update
	void update(float DeltaTime) override;

	// textures used for animation
	void setAnimationTextures(const std::vector<SDL_Texture*>& textures);

	float getAnimationFPS() const { return AnimationFPS; }
	void setAnimationFPS(float FPS) { AnimationFPS = FPS; }
private:
	// textures in the animation
	std::vector<SDL_Texture*> vAnimationTextures;
	
	float currentFrame;
	
	float AnimationFPS; // frame rate
};