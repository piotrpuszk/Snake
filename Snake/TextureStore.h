#pragma once
#include <SFML/Graphics.hpp>

class TextureStore
{
public:
	TextureStore();

	const sf::Texture& getTestTexture() const noexcept;
private:
	sf::Texture testTexture;
};

