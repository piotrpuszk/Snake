#pragma once
#include <SFML/Graphics.hpp>
#include "MeshRenderer.h"

class TurnPoint
{
public:
	TurnPoint(sf::Vector2f position, sf::Vector2f directionFrom, sf::Vector2f directionTo, MeshRenderer* meshRenderer);
	sf::Vector2f getPosition() const noexcept;
	sf::Vector2f getDirectionFrom() const noexcept;
	sf::Vector2f getDirectionTo() const noexcept;
	MeshRenderer* getMeshRenderer();
	bool operator==(const TurnPoint& rightSide);
	bool operator!=(const TurnPoint& rightSide);
private:
	sf::Vector2f position;
	sf::Vector2f directionFrom;
	sf::Vector2f directionTo;
	MeshRenderer* meshRenderer;
};

