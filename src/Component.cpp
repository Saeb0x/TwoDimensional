#include "Component.h"
#include "Actor.h"

Component::Component(Actor* owner, int updateOrder) : ownerActor(owner), UpdateOrder(updateOrder)
{
	// add to actor's vector of components
	ownerActor->addComponent(this);
}

Component::~Component()
{
	ownerActor->removeComponent(this);
}

void Component::update(float DeltaTime)
{
}