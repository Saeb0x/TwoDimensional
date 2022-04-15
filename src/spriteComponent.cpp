#include "spriteComponent.h"
#include "Actor.h"
#include "Game.h"

spriteComponent::spriteComponent(Actor* owner, int drawOrder) : Component(owner), Texture(nullptr), DrawOrder(drawOrder), textureWidth(0), textureHeight(0)
{
	ownerActor->getGame()->addSprite(this);
}

spriteComponent::~spriteComponent()
{
	ownerActor->getGame()->removeSprite(this);
}

void spriteComponent::draw(SDL_Renderer* Renderer)
{
	if (Texture)
	{
		SDL_Rect rect;

		// scale the width and height by ownerActor's scale
		rect.w = static_cast<int>(textureWidth * ownerActor->GetScale());
		rect.h = static_cast<int>(textureHeight * ownerActor->GetScale());

		// center the rectangle around ownerActor's position
		rect.x = static_cast<int>(ownerActor->GetPosition().x - rect.w / 2);
		rect.y = static_cast<int>(ownerActor->GetPosition().y - rect.h / 2);

		SDL_RenderCopyEx(Renderer, Texture, nullptr, &rect, -BasicMath::RadiansToDegrees(ownerActor->GetRotation()), nullptr, SDL_FLIP_NONE);

	}
}

void spriteComponent::setTexture(SDL_Texture* texture)
{
	Texture = texture;
	SDL_QueryTexture(texture, nullptr, nullptr, &textureWidth, &textureHeight); // get the width & height of texture
}