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

	auto snake{ gameObjectFactory.create<Snake>() };

	std::vector<Consumable*> consumables{};
	consumables.push_back(gameObjectFactory.create<Consumable>(sf::Vector2f{ 100.f, 100.f }, 1));

	std::vector<Wall*> walls
	{ 
		gameObjectFactory.create<Wall>(sf::Vector2f{0, 0}, sf::Vector2f{ 50, 600 }), 
		gameObjectFactory.create<Wall>(sf::Vector2f{0, 0}, sf::Vector2f{ 800, 50 }), 
		gameObjectFactory.create<Wall>(sf::Vector2f{0, 550}, sf::Vector2f{ 800, 50 }), 
		gameObjectFactory.create<Wall>(sf::Vector2f{750, 0}, sf::Vector2f{ 50, 600 }), 
	};

	auto backgroundTexture{ gameObjectFactory.create<BackgroundTexture>(sf::Vector2f{}, sf::Vector2f{800, 600}) };

	CollisionSystem collisionSystem{};
	for (const auto& e : snake->getComponents<BoxCollider>())
	{
		collisionSystem.addSnakeCollider(ObjectCollider{ snake, e });
	}
	for (auto& consumable : consumables)
	{
		for (const auto& e : consumable->getComponents<BoxCollider>())
		{
			collisionSystem.addOtherCollider(ObjectCollider{ consumable, e });
		}
	}
	for (auto& wall : walls)
	{
		for (const auto& e : wall->getComponents<BoxCollider>())
		{
			collisionSystem.addOtherCollider(ObjectCollider{ wall, e });
		}
	}
	Renderer renderer{ gameObjectStore };
	GameLoop gameLoop{ gameObjectStore, gameSettings, renderer, collisionSystem, window };
	KeyHandler::initialize();

	GameObjectInstantiator::setGameObjectFactory(&gameObjectFactory);
	GameObjectInstantiator::setGameObjectStore(&gameObjectStore);
	GameObjectInstantiator::setCollisionSystem(&collisionSystem);

	gameObjectFactory.create<ConsumablesSpawner>(gameSettings, sf::seconds(1.f));


	while (window.isOpen())
	{
		gameLoop.execute();
	}

	return 0;
}