#pragma once
#include "MathForGames.h"
#include <vector>
#include <cstdint>

class Actor
{
public:
	// for actor's state
	enum class State
	{
		Active,
		Paused,
		Dead
	};

	Actor(class Game* game);
	virtual ~Actor();

	void update(float DeltaTime);
	// update all components attached to actor
	void updateComponents(float DeltaTime);
	// specific actor update
	virtual void updateActor(float DeltaTime);

	void processInput(const uint8_t* keyState);
	// actor specified input code (overridable)
	virtual void actorInput(const uint8_t* keyState);

	const Vector2D& GetPosition() const { return Position; }
	void SetPosition(const Vector2D& iPosition) { Position = iPosition; }
	float GetScale() const { return Scale; }
	void SetScale(float iScale) { Scale = iScale; }
	float GetRotation() const { return Rotation; }
	void SetRotation(float iRotation) { Rotation = iRotation; } // in radians
	
	State GetState() const { return mState; }
	void SetState(State iState) { mState = iState; }

	Vector2D GetForward() const { return Vector2D(BasicMath::Cosine(Rotation), -BasicMath::Sine(Rotation)); }

	class Game* getGame() { return mGame; }

	void addComponent(class Component* component);
	void removeComponent(class Component* component);

private:
	State mState; 

	// transform
	Vector2D Position;
	float Scale;
	float Rotation;

	std::vector<class Component*> vComponents;
	class Game* mGame;
};