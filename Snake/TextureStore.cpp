#include "TextureStore.h"

TextureStore::TextureStore()
{
	test.loadFromFile("testTexture2.jpg");
	food01.loadFromFile("food01.png");
	brick01.loadFromFile("polyHavenBrick03.jpg");
	background.loadFromFile("polyHavenBrownMudLeaves.jpg");
}

const sf::Texture& TextureStore::getTest() const noexcept
{
	return test;
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
