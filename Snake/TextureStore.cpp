#include "TextureStore.h"

TextureStore::TextureStore()
{
	snakePart.loadFromFile("snakePartTexture.png");
	turnPointLeftBottom.loadFromFile("turnPointLeftBottomTexture.png");
	turnPointLeftUp.loadFromFile("turnPointLeftUp.png");
	turnPointRightBottom.loadFromFile("turnPointRightBottomTexture.png");
	turnPointRightUp.loadFromFile("turnPointRightUpTexture.png");
	turnPoint.loadFromFile("turnPointTexture.png");
	food01.loadFromFile("food01.png");
	brick01.loadFromFile("polyHavenBrick03.jpg");
	background.loadFromFile("polyHavenBrownMudLeaves.jpg");
	snakeHead.loadFromFile("snakeHead.png");
	snakeTail.loadFromFile("snakeTail.png");
}

const sf::Texture& TextureStore::getSnakePart() const noexcept
{
	return snakePart;
}

const sf::Texture& TextureStore::getTurnPoint() const noexcept
{
	return turnPoint;
}

const sf::Texture& TextureStore::getTurnPointLeftBottom() const noexcept
{
	return turnPointLeftBottom;
}

const sf::Texture& TextureStore::getTurnPointLeftUp() const noexcept
{
	return turnPointLeftUp;
}

const sf::Texture& TextureStore::getTurnPointRightBottom() const noexcept
{
	return turnPointRightBottom;
}

const sf::Texture& TextureStore::getTurnPointRightUp() const noexcept
{
	return turnPointRightUp;
}

const sf::Texture& TextureStore::getFood01() const noexcept
{
	return food01;
}

const sf::Texture& TextureStore::getBrick01() const noexcept
{
	return brick01;
}

const sf::Texture& TextureStore::getBackground() const noexcept
{
	return background;
}

const sf::Texture& TextureStore::getSnakeHead() const noexcept
{
	return snakeHead;
}

const sf::Texture& TextureStore::getSnakeTail() const noexcept
{
	return snakeTail;
}
