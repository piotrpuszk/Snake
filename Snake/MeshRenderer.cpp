#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(sf::Sprite sprite, int renderPriority)
	:
	sprite{ sprite },
	renderPriority{ renderPriority }
{
}

sf::Sprite MeshRenderer::getSprite() const noexcept
{
	return sprite;
}


void MeshRenderer::setSprite(sf::Sprite value)
{
	sprite = value;
}

void MeshRenderer::rotate(float angle) noexcept
{
	sprite.rotate(angle);
}

void MeshRenderer::setPosition(sf::Vector2f position)
{
	sprite.setPosition(position);
}

void MeshRenderer::setRotation(float rotation)
{
	sprite.setRotation(rotation);
}

int MeshRenderer::getRenderPriority() const noexcept
{
	return renderPriority;
}

bool MeshRenderer::operator<(const MeshRenderer& rightSide)
{
	return renderPriority < rightSide.renderPriority;
}
