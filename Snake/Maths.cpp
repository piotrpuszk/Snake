#include "Maths.h"
#include <cmath>

float Maths::dot(sf::Vector2f v1, sf::Vector2f v2) noexcept
{
	return v1.x * v2.x + v1.y * v2.y;
}

float Maths::magnitude(sf::Vector2f v) noexcept
{
	return sqrt(v.x * v.x + v.y * v.y);
}

float Maths::magnitudeSquared(sf::Vector2f v) noexcept
{
	return v.x * v.x + v.y * v.y;
}

sf::Vector2f Maths::round(sf::Vector2f v) noexcept
{
	v.x = std::round(v.x);
	v.y = std::round(v.y);

	return v;
}
