#include "Map.h"

Map::Map(sf::Vector2f size,
	float tileSize)
	:
	size{ size },
	tileSize{ tileSize }
{
}

sf::Vector2f Map::getSize() const noexcept
{
	return size;
}

float Map::getTileSize() const noexcept
{
	return tileSize;
}
