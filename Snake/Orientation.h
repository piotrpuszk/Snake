#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include "WorldDirection.h"

class Orientation
{
public:
	static bool isUp(sf::Vector2f direction) noexcept;
	static bool isDown(sf::Vector2f direction) noexcept;
	static bool isRight(sf::Vector2f direction) noexcept;
	static bool isLeft(sf::Vector2f direction) noexcept;
	static float getAngle(sf::Vector2f from, sf::Vector2f to) noexcept;
	static std::vector<sf::Vector2f> getOrientation(sf::Vector2f direction) noexcept;
private:
	static int getKey(const sf::Vector2f& direction);

	static float angle;
	static std::unordered_map<int, std::vector<sf::Vector2f>> orientations;
};

