#include "Renderer.h"

Renderer::Renderer(vector<MeshRenderer>& meshRenderers)
	:
	meshRenderers{ meshRenderers }
{
}

void Renderer::render(sf::RenderWindow& window)
{
	for (const auto& meshRenderer : meshRenderers)
	{
		window.draw(meshRenderer.getSprite());
	}
}
