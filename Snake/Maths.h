#pragma once
#include <SFML/Graphics.hpp>

class Maths
{
public:
	static float dot(sf::Vector2f v1, sf::Vector2f v2) noexcept;
	static float magnitude(sf::Vector2f v) noexcept;
	static float magnitudeSquared(sf::Vector2f v) noexcept;
	static sf::Vector2f round(sf::Vector2f v) noexcept;
};

