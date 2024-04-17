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
	Transform& setLeft(sf::Vector2f newLeft);
	Transform& setRight(sf::Vector2f newRight);
	sf::Vector2f getPosition() const noexcept;
	sf::Vector2f getForward() const noexcept;
	sf::Vector2f getLeft() const noexcept;
	sf::Vector2f getRight() const noexcept;
private:
	sf::Vector2f position;
	sf::Vector2f forward;
	sf::Vector2f left;
	sf::Vector2f right;
};

