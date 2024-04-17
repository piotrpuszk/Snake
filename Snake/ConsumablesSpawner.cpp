#include "ConsumablesSpawner.h"
#include "Consumable.h"
#include "GameObjectInstantiator.h"
#include <iostream>

ConsumablesSpawner::ConsumablesSpawner(const GameSettings& gameSettings, sf::Time spawnInterval)
	:
	gameSettings{ gameSettings },
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
		auto consumable = GameObjectInstantiator::instantiate<Consumable>
		(
			sf::Vector2f
			{
				static_cast<float>(std::rand() % gameSettings.getMapSize().x),
				static_cast<float>(std::rand() % gameSettings.getMapSize().y)
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
