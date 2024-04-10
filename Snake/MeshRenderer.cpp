#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(sf::Sprite sprite)
	:
	sprite{ sprite }
{
}

sf::Sprite MeshRenderer::getSprite() const noexcept
{
	return sprite;
}

void MeshRenderer::rotate(float angle) noexcept
{
	sprite.rotate(angle);
}

void MeshRenderer::updatePosition(sf::Vector2f position)
{
	sprite.setPosition(position);
}
