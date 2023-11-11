#pragma once
#include <SFML/Graphics.hpp>

class TurnPoint
{
public:
	TurnPoint(sf::Vector2f position, sf::Vector2f direction);
	sf::Vector2f getPosition() const noexcept;
	sf::Vector2f getDirection() const noexcept;
private:
	sf::Vector2f position;
	sf::Vector2f direction;
};

