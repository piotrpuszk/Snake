#include "Orientation.h"
#include "WorldDirection.h"

float Orientation::angle = 90.f;

bool Orientation::isUp(sf::Vector2f direction)
{
	return direction == WorldDirection::up;
}

bool Orientation::isDown(sf::Vector2f direction)
{
	return direction == WorldDirection::down;
}

bool Orientation::isRight(sf::Vector2f direction)
{
	return direction == WorldDirection::right;
}

bool Orientation::isLeft(sf::Vector2f direction)
{
	return direction == WorldDirection::left;
}

float Orientation::getAngle(sf::Vector2f from, sf::Vector2f to)
{
	if (isUp(from) && isRight(to))
	{
		return angle;
	}

	if (isUp(from) && isLeft(to))
	{
		return -angle;
	}

	if (isDown(from) && isRight(to))
	{
		return -angle;
	}

	if (isDown(from) && isLeft(to))
	{
		return angle;
	}

	if (isRight(from) && isUp(to))
	{
		return -angle;
	}

	if (isRight(from) && isDown(to))
	{
		return angle;
	}

	if (isLeft(from) && isUp(to))
	{
		return angle;
	}

	if (isLeft(from) && isDown(to))
	{
		return -angle;
	}

	return 0.f;
}