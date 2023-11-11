#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>

class MeshRenderer : public Component
{
public:
	~MeshRenderer() = default;

	sf::Sprite getSprite() const noexcept;
private:
	sf::Sprite sprite;
};

