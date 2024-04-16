#include "SpawnerOfConsumables.h"
#include "Consumable.h"
#include "GameObjectInstantiator.h"
#include <iostream>

SpawnerOfConsumables::SpawnerOfConsumables(const GameSettings& gameSettings, sf::Time spawnInterval)
	:
	gameSettings{ gameSettings },
	spawnInterval{ spawnInterval },
	timeElapsed{},
	clock{}
{
	std::srand(1);
}

bool SpawnerOfConsumables::canSpawn()
{
	return timeElapsed >= spawnInterval;
}

void SpawnerOfConsumables::awake()
{
	clock = {};
}

void SpawnerOfConsumables::update()
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

	/*	std::cout << consumable->getComponent<Transform>()->getPosition().x << " "
			<< consumable->getComponent<Transform>()->getPosition().y << std::endl;*/
	}
}

void SpawnerOfConsumables::fixedUpdate()
{
}

void SpawnerOfConsumables::onEnterCollision(GameObject* gameObject)
{
}
