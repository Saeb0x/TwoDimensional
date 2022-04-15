#include "inputComponent.h"
#include "Actor.h"

InputComponent::InputComponent(class Actor* owner) : MoveComponent(owner), maxForwardSpeed(0), maxAngularSpeed(0), forwardKey(0), backKey(0), clockwiseKey(0), antiClockwiseKey(0) {}

void InputComponent::processInput(const uint8_t* keyState)
{
	// forward speed for moveComponent
	float forwardSpeed = 0.0f;
	if (keyState[forwardKey])
	{
		forwardSpeed += maxForwardSpeed;
	}
	if (keyState[backKey])
	{
		forwardSpeed -= maxForwardSpeed;
	}
	setForwardSpeed(forwardSpeed);

	// angular speed for moveComponent
	float angularSpeed = 0.0f;
	if (keyState[clockwiseKey])
	{
		angularSpeed += maxAngularSpeed;
	}
	if (keyState[antiClockwiseKey])
	{
		angularSpeed -= maxAngularSpeed;
	}
	setAngularSpeed(angularSpeed);
}
