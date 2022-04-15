#pragma once
#include "moveComponent.h"
#include <cstdint>

class InputComponent : public MoveComponent
{
public:
	InputComponent(class Actor* owner);

	void processInput(const uint8_t* keyState) override;

	float getMaxForward() const { return maxForwardSpeed; }
	float getMaxAngular() const { return maxAngularSpeed; }
	int getForwardKey() const { return forwardKey; }
	int getBackKey() const { return backKey; }
	int getClockwiseKey() const { return clockwiseKey; }
	int getCounterClockwiseKey() const { return antiClockwiseKey; }

	void setMaxForwardSpeed(float speed) { maxForwardSpeed = speed; }
	void setMaxAngularSpeed(float speed) { maxAngularSpeed = speed; }
	void setForwardKey(int key) { forwardKey = key; }
	void setBackKey(int key) { backKey = key; }
	void setClockwiseKey(int key) { clockwiseKey = key; }
	void setCounterClockwiseKey(int key) { antiClockwiseKey = key; }
private:
	float maxForwardSpeed;
	float maxAngularSpeed;

	// for forward and back movement
	int forwardKey;
	int backKey;

	// for angular movement
	int clockwiseKey;
	int antiClockwiseKey;
};
