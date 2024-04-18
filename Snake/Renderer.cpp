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

	for (const auto& e: gameObjectStore.getMeshRenderers())
	{
		window.draw(e->getSprite());
	}

	window.display();
}
