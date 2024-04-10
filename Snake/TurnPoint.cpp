#include "TurnPoint.h"
#include <iostream>

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

bool TurnPoint::operator==(const TurnPoint& rightSide)
{
	return getPosition() == rightSide.getPosition() && getDirection() == rightSide.getDirection();
}

bool TurnPoint::operator!=(const TurnPoint& rightSide)
{
	return !(*this == rightSide);
}
