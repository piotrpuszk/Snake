#pragma once
#include <SFML/Graphics.hpp>

class TurnPoint
{
public:
	TurnPoint(sf::Vector2f position, sf::Vector2f directionFrom, sf::Vector2f directionTo);
	sf::Vector2f getPosition() const noexcept;
	sf::Vector2f getDirectionFrom() const noexcept;
	sf::Vector2f getDirectionTo() const noexcept;
	bool operator==(const TurnPoint& rightSide);
	bool operator!=(const TurnPoint& rightSide);
private:
	sf::Vector2f position;
	sf::Vector2f directionFrom;
	sf::Vector2f directionTo;
};

