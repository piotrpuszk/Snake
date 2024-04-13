#include "Renderer.h"

Renderer::Renderer(GameObjectStore& gameObjectStore)
	:
	gameObjectStore{ gameObjectStore }
{
}

void Renderer::render(sf::RenderWindow& window)
{
	window.clear(sf::Color::Black);

	for (auto& meshRenderer : gameObjectStore.getMeshRenderers())
	{
		window.draw(meshRenderer->getSprite());
	}

	window.display();
}
