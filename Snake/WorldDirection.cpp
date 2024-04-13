#include "WorldDirection.h"

sf::Vector2f WorldDirection::up = { 0, -1 };
sf::Vector2f WorldDirection::down = { 0, 1 };
sf::Vector2f WorldDirection::right = { 1, 0 };
sf::Vector2f WorldDirection::left = { -1, 0 };

bool WorldDirection::areOppositeDirections(sf::Vector2f direction1, sf::Vector2f direction2) noexcept
{
	return (direction1.x == direction2.x && direction1.y == -direction2.y)
		|| (direction1.y == direction2.y && direction1.x == -direction2.x);
}