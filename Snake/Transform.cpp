#include "Transform.h"

Transform& Transform::setPosition(sf::Vector2f newPosition)
{
	position = newPosition;
	return *this;
}

Transform& Transform::setForward(sf::Vector2f newForward)
{
	forward = newForward;
	return *this;
}

sf::Vector2f Transform::getPosition() const
{
	return position;
}

sf::Vector2f Transform::getForward() const
{
	return forward; 
}
