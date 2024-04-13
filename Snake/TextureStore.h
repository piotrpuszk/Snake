#pragma once
#include <SFML/Graphics.hpp>

class TextureStore
{
public:
	TextureStore();

	const sf::Texture& getTestTexture() const noexcept;
	const sf::Texture& getFood01Texture() const noexcept;
private:
	sf::Texture testTexture;
	sf::Texture food01Texture;
};

