#pragma once
#include <SFML/Graphics.hpp>
#include "Component.h"

class Transform : Component
{
public:
	~Transform() = default;

	Transform& setPosition(sf::Vector2f newPosition);
	Transform& setForward(sf::Vector2f newForward);
	sf::Vector2f getPosition() const;
	sf::Vector2f getForward() const;
private:
	sf::Vector2f position;
	sf::Vector2f forward;
};

