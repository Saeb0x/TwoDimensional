#include "animatedSpriteComponent.h"
#include "MathForGames.h"


animatedSpriteComponent::animatedSpriteComponent(Actor* owner, int drawOrder) : spriteComponent(owner, drawOrder), currentFrame(0.0f), AnimationFPS(24.0f) 
{}

void animatedSpriteComponent::update(float DeltaTime)
{
	spriteComponent::update(DeltaTime);

	if (vAnimationTextures.size() > 0)
	{
		currentFrame += AnimationFPS * DeltaTime; // update current frame based on the frame rate and delta time

		while (currentFrame >= vAnimationTextures.size())
		{
			currentFrame -= vAnimationTextures.size();
		}

		setTexture(vAnimationTextures[static_cast<int>(currentFrame)]);
	}
}

void animatedSpriteComponent::setAnimationTextures(const std::vector<SDL_Texture*>& textures)
{
	vAnimationTextures = textures;
	if (vAnimationTextures.size() > 0)
	{
		// first frame is set to be the active texture
		currentFrame = 0.0f;
		setTexture(vAnimationTextures[0]);
	}
}