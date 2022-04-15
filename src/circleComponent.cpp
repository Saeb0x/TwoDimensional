#include "circleComponent.h"
#include "Actor.h"

CircleComponent::CircleComponent(class Actor* owner) : Component(owner), Radius(0.0f) {}

const Vector2D& CircleComponent::getCenter() const
{
	return ownerActor->GetPosition();
}

float CircleComponent::getRadius() const
{
	return ownerActor->GetScale() * Radius;
}

bool Intersection(const CircleComponent& a, const CircleComponent& b)
{
	// The distance squared
	Vector2D diff = a.getCenter() - b.getCenter();
	float distSq = diff.LengthSquared();

	// The sum of radii squared
	float radiiSq = a.getRadius() + b.getRadius();
	radiiSq *= radiiSq;

	return distSq <= radiiSq;
}

