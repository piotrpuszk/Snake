#pragma once
#include <SFML/Graphics.hpp>

class Maths
{
public:
	static float dot(sf::Vector2f v1, sf::Vector2f v2);
	static float magnitude(sf::Vector2f v);
	static sf::Vector2f round(sf::Vector2f v);
};

