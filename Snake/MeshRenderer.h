#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>

class MeshRenderer : public Component
{
public:
	MeshRenderer(sf::Sprite sprite);
	~MeshRenderer() = default;

	sf::Sprite getSprite() const noexcept;
	void rotate(float angle) noexcept;
	void setPosition(sf::Vector2f position);
private:
	sf::Sprite sprite;
};

