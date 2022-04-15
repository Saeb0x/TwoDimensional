#include "moveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(class Actor* owner, int updateOrder) : Component(owner, updateOrder), angularSpeed(0.0f), forwardSpeed(0.0f) {}

void MoveComponent::update(float DeltaTime)
{
	if (!BasicMath::NearZero(angularSpeed))
	{
		float rotation = ownerActor->GetRotation();
		rotation += angularSpeed * DeltaTime;
		ownerActor->SetRotation(rotation);
	}

	if (!BasicMath::NearZero(forwardSpeed))
	{
		Vector2D position = ownerActor->GetPosition();
		position += ownerActor->GetForward() * forwardSpeed * DeltaTime;

		if (position.x < 0.0f)
		{
			position.x = 1022.0f; // screen width = 1024
		}
		else if (position.x > 1024.0f)
		{
			position.x = 2.0f;
		}

		if (position.y < 0.0f)
		{
			position.y = 766.0f; // screen height = 768
		}
		else if (position.y > 768.0f)
		{
			position.y = 2.0f;
		}
		ownerActor->SetPosition(position);
	}
}