#include "Renderer.h"
#include "Consumable.h"
#include <iostream>

Renderer::Renderer(GameObjectStore& gameObjectStore)
	:
	gameObjectStore{ gameObjectStore }
{
}

void Renderer::render(sf::RenderWindow& window) const
{
	window.clear(sf::Color::Black);

	for (const auto& gameObject : gameObjectStore.getGameObjects())
	{
		for (const auto& meshRenderer : gameObject->getMeshRenderers())
		{
			window.draw(meshRenderer->getSprite());
		}
	}

	window.display();
}
