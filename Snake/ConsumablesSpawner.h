#pragma once
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "GameSettings.h"

class ConsumablesSpawner : public GameObject
{
public:
	ConsumablesSpawner(const GameSettings& gameSettings, sf::Time spawnInterval);
	
private:
	sf::Time spawnInterval;
	sf::Time timeElapsed;
	sf::Clock clock;
	const GameSettings& gameSettings;

	void awake() override;
	void update() override;
	void fixedUpdate() override;
	void onEnterCollision(GameObject* gameObject) override;
	bool canSpawn();
};