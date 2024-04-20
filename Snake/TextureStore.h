#pragma once
#include <SFML/Graphics.hpp>
#include "Component.h"

class TextureStore : public Component
{
public:
	TextureStore();

	const sf::Texture& getSnakePart() const noexcept;
	const sf::Texture& getTurnPoint() const noexcept;
	const sf::Texture& getTurnPointLeftBottom() const noexcept;
	const sf::Texture& getTurnPointLeftUp() const noexcept;
	const sf::Texture& getTurnPointRightBottom() const noexcept;
	const sf::Texture& getTurnPointRightUp() const noexcept;
	const sf::Texture& getFood01() const noexcept;
	const sf::Texture& getBrick01() const noexcept;
	const sf::Texture& getBackground() const noexcept;
	const sf::Texture& getSnakeHead() const noexcept;
	const sf::Texture& getSnakeTail() const noexcept;
	const sf::Texture& getGameOver() const noexcept;
private:
	sf::Texture snakePart;
	sf::Texture turnPoint;
	sf::Texture turnPointLeftBottom;
	sf::Texture turnPointLeftUp;
	sf::Texture turnPointRightBottom;
	sf::Texture turnPointRightUp;
	sf::Texture food01;
	sf::Texture brick01;
	sf::Texture background;
	sf::Texture snakeHead;
	sf::Texture snakeTail;
	sf::Texture gameOver;
};

