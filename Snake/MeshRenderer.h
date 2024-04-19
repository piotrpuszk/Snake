#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>

class MeshRenderer : public Component
{
public:
	MeshRenderer(sf::Sprite sprite, int renderPriority = 0);
	~MeshRenderer() = default;

	sf::Sprite getSprite() const noexcept;
	void setSprite(sf::Sprite value);
	void rotate(float angle) noexcept;
	void setPosition(sf::Vector2f position);
	void setRotation(float rotation);
	int getRenderPriority() const noexcept;
	bool operator<(const MeshRenderer& rightSide);
private:
	sf::Sprite sprite;
	int renderPriority;
};

