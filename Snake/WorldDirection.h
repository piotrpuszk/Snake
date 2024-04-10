#pragma once
#include <SFML/Graphics.hpp>

class WorldDirection
{
public:
	static sf::Vector2f up;
	static sf::Vector2f down;
	static sf::Vector2f right;
	static sf::Vector2f left;

	static bool areOppositeDirections(sf::Vector2f direction1, sf::Vector2f direction2);
};