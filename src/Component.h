#pragma once
#include <cstdint>

class Component
{
public:
	// the lower the update order is, the earlier the component updates
	Component(class Actor* owner, int updateOrder = 100); 
	virtual ~Component();
	
	// update certain component
	virtual void update(float DeltaTime);

	// process input for this specific component
	virtual void processInput(const uint8_t* keyState) {}

	int GetUpdateOrder() const { return UpdateOrder; }

protected:
	class Actor* ownerActor;
	int UpdateOrder;
};