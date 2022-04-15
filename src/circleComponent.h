#pragma once
#include "Component.h"
#include "MathForGames.h"

// for the use of collisions
class CircleComponent : public Component
{
public:
	CircleComponent(class Actor* owner);
	
	void setRadius(float radius) { Radius = radius; }
	float getRadius() const;
	const Vector2D& getCenter() const;
private:
	float Radius;
};

bool Intersection(const CircleComponent& a, const CircleComponent& b); // detect intersection