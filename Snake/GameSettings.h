#pragma once
#include <SFML/Graphics.hpp>

class GameSettings
{
public:
	GameSettings(sf::Time fixedTimeStep,
		sf::Vector2u mapSize);

	sf::Time getFixedTimeStep() const;
	sf::Vector2u getMapSize() const;
private:
	sf::Time fixedTimeStep;
	sf::Vector2u mapSize;
};

