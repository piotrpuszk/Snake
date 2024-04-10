#pragma once
#include <SFML/Graphics.hpp>

class TurnPoint
{
public:
	TurnPoint(sf::Vector2f position, sf::Vector2f direction);
	sf::Vector2f getPosition() const noexcept;
	sf::Vector2f getDirection() const noexcept;
	bool operator==(const TurnPoint& rightSide);
	bool operator!=(const TurnPoint& rightSide);

private:
	sf::Vector2f position;
	sf::Vector2f direction;
};

