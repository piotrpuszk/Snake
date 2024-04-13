#include "Consumable.h"
#include "GameObjectInstantiator.h"

Consumable::Consumable(size_t growSize)
	:
	growSize{ growSize }
{
}

size_t Consumable::getGrowSize() const noexcept
{
	return growSize;
}

void Consumable::awake()
{
}

void Consumable::update()
{
}

void Consumable::fixedUpdate()
{
}

void Consumable::onEnterCollision(GameObject* gameObject)
{
	GameObjectInstantiator::destroy(this);
}
