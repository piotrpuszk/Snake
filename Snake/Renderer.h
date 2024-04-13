#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "GameObjectStore.h"

class Renderer
{
public:
	Renderer(GameObjectStore& gameObjectStore);

	void render(sf::RenderWindow& window) const;
private:
	GameObjectStore& gameObjectStore;
};

