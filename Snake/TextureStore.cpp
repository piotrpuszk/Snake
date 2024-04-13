#include "TextureStore.h"

TextureStore::TextureStore()
{
	testTexture.loadFromFile("testTexture2.jpg");
	food01Texture.loadFromFile("food01.png");
}

const sf::Texture& TextureStore::getTestTexture() const noexcept
{
	return testTexture;
}

const sf::Texture& TextureStore::getFood01Texture() const noexcept
{
	return food01Texture;
}
