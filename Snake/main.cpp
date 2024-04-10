#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <iostream>
#include "GameObjectFactory.h"
#include "Renderer.h"
#include "GameSettings.h"
#include "CollisionSystem.h"
#include "GameLoop.h"
#include "GameObjectStore.h"
#include "KeyHandler.h"
#include "GameObjectInstantiator.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "My window");
	TextureStore textureStore{};
	GameObjectStore gameObjectStore{};
	GameObjectFactory gameObjectFactory{ textureStore, gameObjectStore };
	auto snake = gameObjectFactory.createSnake();
	GameSettings gameSettings{ sf::seconds(0.02f), {800, 600} };
	std::vector<ObjectCollider> objectColliders{};
	GameObject* snakeGO = snake.get();
	Renderer renderer{ gameObjectStore };
	objectColliders.push_back(ObjectCollider{ snakeGO, snakeGO->getComponent<BoxCollider>() });
	CollisionSystem collisionSystem{ objectColliders };
	GameLoop gameLoop{ gameObjectStore, gameSettings, renderer, collisionSystem, window };
	KeyHandler::initialize();

	GameObjectInstantiator::setGameObjectFactory(&gameObjectFactory);
	GameObjectInstantiator::setGameObjectStore(&gameObjectStore);

	while (window.isOpen())
	{
		gameLoop.execute();
	}

	return 0;
}