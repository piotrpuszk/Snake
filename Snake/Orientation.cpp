#include "Orientation.h"
#include "WorldDirection.h"

float Orientation::angle = 90.f;
std::unordered_map<int, std::vector<sf::Vector2f>> Orientation::orientations =
{
	{0, {{1.f, 0.f}, {0.f, -1.f}, {-1.f, 0.f}}},
	{1, {{-1.f, 0.f}, {0.f, 1.f}, {1.f, 0.f}}},
	{2, {{0.f, -1.f}, {-1.f, 0.f}, {0.f, 1.f}}},
	{3, {{0.f, 1.f}, {1.f, 0.f}, {0.f, -1.f}}},
};

bool Orientation::isUp(sf::Vector2f direction) noexcept
{
	return direction == WorldDirection::up;
}

bool Orientation::isDown(sf::Vector2f direction) noexcept
{
	return direction == WorldDirection::down;
}

bool Orientation::isRight(sf::Vector2f direction) noexcept
{
	return direction == WorldDirection::right;
}

bool Orientation::isLeft(sf::Vector2f direction) noexcept
{
	return direction == WorldDirection::left;
}

bool Orientation::isUpOrDown(sf::Vector2f direction) noexcept
{
	return isUp(direction) or isDown(direction);
}

bool Orientation::isLeftOrRight(sf::Vector2f direction) noexcept
{
	return isLeft(direction) || isRight(direction);
}

float Orientation::getAngle(sf::Vector2f from, sf::Vector2f to) noexcept
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

std::vector<sf::Vector2f> Orientation::getOrientation(sf::Vector2f direction) noexcept
{
	return orientations[getKey(direction)];
}

int Orientation::getKey(const sf::Vector2f& direction)
{
	if (isUp(direction))
	{
		return 0;
	}
	if (isDown(direction))
	{
		return 1;
	}
	if (isLeft(direction))
	{
		return 2;
	}
	if (isRight(direction))
	{
		return 3;
	}
}
