#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "GameObjectStore.h"

using namespace std;

class Renderer
{
public:
	Renderer(GameObjectStore& gameObjectStore);

	void render(sf::RenderWindow& window);
private:
	GameObjectStore& gameObjectStore;
};

