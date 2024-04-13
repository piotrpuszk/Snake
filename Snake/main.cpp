#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
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
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
	GameSettings gameSettings{ sf::seconds(0.02f), {800, 600} };

	TextureStore textureStore{};
	GameObjectStore gameObjectStore{};
	GameObjectFactory gameObjectFactory{ textureStore, gameObjectStore };
	auto snake = gameObjectFactory.createSnake();
	std::vector<Consumable*> consumables{};
	consumables.push_back(gameObjectFactory.createFood01({ 100.f, 100.f }));
	consumables.push_back(gameObjectFactory.createFood01({ 200.f, 200.f }));
	consumables.push_back(gameObjectFactory.createFood01({ 300.f, 300.f }));
	consumables.push_back(gameObjectFactory.createFood01({ 400.f, 400.f }));
	consumables.push_back(gameObjectFactory.createFood01({ 500.f, 400.f }));
	consumables.push_back(gameObjectFactory.createFood01({ 700.f, 400.f }));
	consumables.push_back(gameObjectFactory.createFood01({ 500.f, 150.f }));
	std::vector<ObjectCollider> objectColliders{};
	for (const auto& e : snake->getComponents<BoxCollider>())
	{
		objectColliders.push_back(ObjectCollider{ snake, e});
	}
	for (auto& consumable : consumables)
	{
		for (const auto& e : consumable->getComponents<BoxCollider>())
		{
			objectColliders.push_back(ObjectCollider{ consumable, e });
		}
	}
	CollisionSystem collisionSystem{ objectColliders };
	Renderer renderer{ gameObjectStore };
	GameLoop gameLoop{ gameObjectStore, gameSettings, renderer, collisionSystem, window };
	KeyHandler::initialize();

	GameObjectInstantiator::setGameObjectFactory(&gameObjectFactory);
	GameObjectInstantiator::setGameObjectStore(&gameObjectStore);
	GameObjectInstantiator::setCollisionSystem(&collisionSystem);

	while (window.isOpen())
	{
		gameLoop.execute();
	}

	return 0;
}