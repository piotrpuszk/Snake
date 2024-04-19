#include "ConsumablesSpawner.h"
#include "Consumable.h"
#include "GameObjectInstantiator.h"
#include <iostream>

ConsumablesSpawner::ConsumablesSpawner(const sf::Vector2f& position, const sf::Vector2f& size, sf::Time spawnInterval)
	:
	position{ position },
	size{ size },
	spawnInterval{ spawnInterval },
	timeElapsed{},
	clock{}
{
	std::srand(1);
}

bool ConsumablesSpawner::canSpawn()
{
	return timeElapsed >= spawnInterval;
}

void ConsumablesSpawner::awake()
{
	clock = {};
}

void ConsumablesSpawner::update()
{
	timeElapsed += clock.restart();

	if (canSpawn())
	{
		timeElapsed = {};
		float signX{ std::rand() % 2 == 0 ? -1.f : 1.f};
		float signY{ std::rand() % 2 == 0 ? -1.f : 1.f};
		auto consumable = GameObjectInstantiator::instantiate<Consumable>
		(
			sf::Vector2f
			{
				position.x + signX * static_cast<float>(std::rand() % static_cast<int>(size.x * 0.5f)),
				position.y + signY * static_cast<float>(std::rand() % static_cast<int>(size.y * 0.5f))
			}
		);
	}
}

void ConsumablesSpawner::fixedUpdate()
{
}

void ConsumablesSpawner::onEnterCollision(GameObject* gameObject)
{
}
