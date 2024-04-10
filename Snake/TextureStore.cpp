#include "TextureStore.h"

TextureStore::TextureStore()
{
	testTexture.loadFromFile("testTexture2.jpg");
}

const sf::Texture& TextureStore::getTestTexture() const noexcept
{
	return testTexture;
}
