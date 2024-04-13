#include "GameSettings.h"

GameSettings::GameSettings(sf::Time fixedTimeStep,
	sf::Vector2u mapSize)
	:
	fixedTimeStep{ fixedTimeStep },
	mapSize{ mapSize }
{
}

sf::Time GameSettings::getFixedTimeStep() const noexcept
{
	return fixedTimeStep;
}

sf::Vector2u GameSettings::getMapSize() const noexcept
{
	return mapSize;
}
