#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

Actor::Actor(Game* game) : mState(State::Active), Position(Vector2D::Zero), Scale(1.0f), Rotation(0.0f), mGame(game) 
{
	mGame->addActor(this);
};


Actor::~Actor()
{
	mGame->removeActor(this);
	while (!vComponents.empty())
	{
		delete vComponents.back();
	}
}

void Actor::update(float DeltaTime)
{
	if (mState == State::Active)
	{
		updateComponents(DeltaTime);
		updateActor(DeltaTime);
	}
}

void Actor::updateComponents(float DeltaTime)
{
	for (auto component : vComponents)
	{
		component->update(DeltaTime);
	}
}

void Actor::updateActor(float DeltaTime)
{
}

void Actor::processInput(const uint8_t* keyState)
{
	if (mState == State::Active)
	{
		// process input for components
		for (auto component : vComponents)
		{
			component->processInput(keyState);
		}

		actorInput(keyState);
	}
}

void Actor::actorInput(const uint8_t* keyState)
{
}

void Actor::addComponent(Component* component)
{
	// the insertion in vComponents has a priority according to the higher order
	int Order = component->GetUpdateOrder();
	auto vIterator = vComponents.begin();
	for (; vIterator != vComponents.end(); ++vIterator)
	{
		if (Order < (*vIterator)->GetUpdateOrder())
		{
			break;
		}
	}

	vComponents.insert(vIterator, component);
}

void Actor::removeComponent(Component* component)
{
	auto vIterator = std::find(vComponents.begin(), vComponents.end(), component);
	if (vIterator != vComponents.end())
	{
		vComponents.erase(vIterator);
	}
}
