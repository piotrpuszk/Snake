#pragma once
#include <SFML/Graphics.hpp>

class Map
{
public:
	Map(sf::Vector2f size, float tileSize);

	sf::Vector2f getSize() const noexcept;
	float getTileSize() const noexcept;
private:
	sf::Vector2f size;
	float tileSize;
};

