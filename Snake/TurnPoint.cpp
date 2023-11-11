#include "TurnPoint.h"

TurnPoint::TurnPoint(sf::Vector2f position, sf::Vector2f direction)
	:
	position{ position },
	direction{ direction }
{
}

sf::Vector2f TurnPoint::getPosition() const noexcept
{
	return position;
}

sf::Vector2f TurnPoint::getDirection() const noexcept
{
	return direction;
}
