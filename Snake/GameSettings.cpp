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

sf::Vector2f GameSettings::getMapSize2f() const noexcept
{
	return sf::Vector2f{ static_cast<float>(mapSize.x), static_cast<float>(mapSize.y) };
}
