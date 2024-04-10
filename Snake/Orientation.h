#pragma once
#include <SFML/Graphics.hpp>

class Orientation
{
public:
	static bool isUp(sf::Vector2f direction);
	static bool isDown(sf::Vector2f direction);
	static bool isRight(sf::Vector2f direction);
	static bool isLeft(sf::Vector2f direction);
	static float getAngle(sf::Vector2f from, sf::Vector2f to);

private:
	static float angle;
};

