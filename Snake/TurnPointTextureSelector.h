#pragma once
#include "Component.h"
#include "TurnPoint.h"
#include "TextureStore.h"
#include <memory>

class TurnPointTextureSelector : public Component
{
public:
	TurnPointTextureSelector(std::unique_ptr<TextureStore>& textureStore);
	const sf::Texture& select(sf::Vector2f from, sf::Vector2f to) const;
private:
	std::unique_ptr<TextureStore> textureStore;
};

