#pragma once
#include <SFML/Graphics.hpp>
#include "Component.h"

class Transform : public Component
{
public:
	Transform();
	~Transform() = default;

	Transform& setPosition(sf::Vector2f newPosition);
	Transform& setForward(sf::Vector2f newForward);
	sf::Vector2f getPosition() const noexcept;
	sf::Vector2f getForward() const noexcept;
private:
	sf::Vector2f position;
	sf::Vector2f forward;
};

