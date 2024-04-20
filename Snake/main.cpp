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

	GameSettings gameSettings{ sf::seconds(0.02f), {1920, 1080} };
	sf::RenderWindow window(sf::VideoMode(gameSettings.getMapSize().x, gameSettings.getMapSize().y), "My window", sf::Style::Default | sf::Style::Fullscreen);

	const auto& map{ gameSettings.getMapSize2f() };

	TextureStore textureStore{};
	GameObjectStore gameObjectStore{};
	GameObjectFactory gameObjectFactory{ textureStore, gameObjectStore };

	auto snake{ gameObjectFactory.create<Snake>() };

	const float wallSize{ 50.f };

	std::vector<Wall*> walls
	{
		gameObjectFactory.create<Wall>(sf::Vector2f{0, 0}, sf::Vector2f{0, 1.f}, map.y / wallSize, wallSize, sf::Vector2f{wallSize * 0.5f, map.y * 0.5f}, sf::Vector2f{wallSize, map.y}),
		gameObjectFactory.create<Wall>(sf::Vector2f{map.x - wallSize, 0}, sf::Vector2f{0, 1.f}, map.y / wallSize, wallSize, sf::Vector2f{map.x - wallSize * 0.5f, map.y * 0.5f}, sf::Vector2f{wallSize, map.y}),
		gameObjectFactory.create<Wall>(sf::Vector2f{0, 0}, sf::Vector2f{1.f, 0}, map.x / wallSize, wallSize, sf::Vector2f{map.x * 0.5f, wallSize * 0.5f}, sf::Vector2f{map.x, wallSize}),
		gameObjectFactory.create<Wall>(sf::Vector2f{0, map.y - wallSize}, sf::Vector2f{1.f, 0}, map.x / wallSize, wallSize, sf::Vector2f{map.x * 0.5f, map.y - wallSize * 0.5f}, sf::Vector2f{map.x, wallSize}),
	};


	auto backgroundTexture{ gameObjectFactory.create<BackgroundTexture>(map) };

	CollisionSystem collisionSystem{};
	for (const auto& e : snake->getComponents<BoxCollider>())
	{
		collisionSystem.addSnakeCollider(ObjectCollider{ snake, e });
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

	const auto additionalMargin{ 50.f };
	gameObjectFactory.create<ConsumablesSpawner>(map * 0.5f, sf::Vector2f{ map.x - wallSize * 2.f - additionalMargin, map.y - wallSize * 2.f - additionalMargin }, sf::seconds(1.f));

	while (window.isOpen())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
			continue;
		}
		gameLoop.execute();
	}

	return 0;
}