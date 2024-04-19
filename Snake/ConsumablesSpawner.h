#pragma once
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "GameSettings.h"

class ConsumablesSpawner : public GameObject
{
public:
	ConsumablesSpawner(const sf::Vector2f& position, const sf::Vector2f& size, sf::Time spawnInterval);
	
private:
	sf::Time spawnInterval;
	sf::Time timeElapsed;
	sf::Clock clock;
	const sf::Vector2f position;
	const sf::Vector2f size;

	void awake() override;
	void update() override;
	void fixedUpdate() override;
	void onEnterCollision(GameObject* gameObject) override;
	bool canSpawn();
};