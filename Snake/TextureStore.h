#pragma once
#include <SFML/Graphics.hpp>

class TextureStore
{
public:
	TextureStore();

	const sf::Texture& getTest() const noexcept;
	const sf::Texture& getFood01() const noexcept;
	const sf::Texture& getBrick01() const noexcept;
	const sf::Texture& getBackground() const noexcept;
private:
	sf::Texture test;
	sf::Texture food01;
	sf::Texture brick01;
	sf::Texture background;
};

