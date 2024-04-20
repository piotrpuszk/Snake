#include "TurnPointTextureSelector.h"
#include <utility>
#include "Orientation.h"

TurnPointTextureSelector::TurnPointTextureSelector(std::unique_ptr<TextureStore>& textureStore)
	:
	textureStore{ std::move(textureStore) }
{
}

const sf::Texture& TurnPointTextureSelector::select(sf::Vector2f from, sf::Vector2f to) const
{
	if (Orientation::isRight(from) && Orientation::isDown(to)
		|| Orientation::isUp(from) && Orientation::isLeft(to))
	{
		return textureStore->getTurnPointLeftBottom();
	}
	else if (Orientation::isRight(from) && Orientation::isUp(to)
		|| Orientation::isDown(from) && Orientation::isLeft(to))
	{
		return textureStore->getTurnPointLeftUp();
	}
	else if (Orientation::isLeft(from) && Orientation::isDown(to)
		|| Orientation::isUp(from) && Orientation::isRight(to))
	{
		return textureStore->getTurnPointRightBottom();
	}
	else if (Orientation::isLeft(from) && Orientation::isUp(to)
		|| Orientation::isDown(from) && Orientation::isRight(to))
	{
		return textureStore->getTurnPointRightUp();
	}

	throw std::invalid_argument("invalid from or to directions");
}
