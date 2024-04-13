#pragma once
#include <SFML/Graphics.hpp>

class GameSettings
{
public:
	GameSettings(sf::Time fixedTimeStep,
		sf::Vector2u mapSize);

	sf::Time getFixedTimeStep() const noexcept;
	sf::Vector2u getMapSize() const noexcept;
private:
	sf::Time fixedTimeStep;
	sf::Vector2u mapSize;
};

