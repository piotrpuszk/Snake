#include "Transform.h"

Transform::Transform()
	:
	position{},
	forward{},
	left{},
	right{}
{
}

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

Transform& Transform::setLeft(sf::Vector2f newLeft)
{
	left = newLeft;
	return *this;
}

Transform& Transform::setRight(sf::Vector2f newRight)
{
	right = newRight;
	return *this;
}

sf::Vector2f Transform::getPosition() const noexcept
{
	return position;
}

sf::Vector2f Transform::getForward() const noexcept
{
	return forward; 
}

sf::Vector2f Transform::getLeft() const noexcept
{
	return left;
}

sf::Vector2f Transform::getRight() const noexcept
{
	return right;
}
