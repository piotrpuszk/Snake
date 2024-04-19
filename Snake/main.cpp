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

	const float wallWidth{ 50.f };
	const sf::Vector2f wallLeftSize{ wallWidth, map.y };
	const sf::Vector2f wallUpSize{ wallWidth, map.x };

	std::vector<Wall*> walls
	{
		gameObjectFactory.create<Wall>(sf::Vector2f{0, 0}, wallLeftSize, sf::Vector2f{wallWidth * 0.5f, map.y * 0.5f}, wallLeftSize),
		gameObjectFactory.create<Wall>(sf::Vector2f{map.x - wallWidth, 0}, wallLeftSize, sf::Vector2f{map.x - wallWidth * 0.5f, map.y * 0.5f}, wallLeftSize),
		gameObjectFactory.create<Wall>(sf::Vector2f{wallWidth, wallWidth}, wallUpSize, sf::Vector2f{map.x * 0.5f, wallWidth * 0.5f}, sf::Vector2f{wallUpSize.y, wallUpSize.x}),
		gameObjectFactory.create<Wall>(sf::Vector2f{wallWidth, map.y}, wallUpSize, sf::Vector2f{map.x * 0.5f, map.y - wallWidth * 0.5f}, sf::Vector2f{wallUpSize.y, wallUpSize.x}),
	};

	walls[2]->getComponent<MeshRenderer>()->rotate(-90);
	walls[3]->getComponent<MeshRenderer>()->rotate(-90);

	auto backgroundTexture{ gameObjectFactory.create<BackgroundTexture>(sf::Vector2f{}, map) };

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
	gameObjectFactory.create<ConsumablesSpawner>(map * 0.5f, sf::Vector2f{ map.x - wallWidth * 2.f - additionalMargin, map.y - wallWidth * 2.f - additionalMargin }, sf::seconds(1.f));


	while (window.isOpen())
	{
		gameLoop.execute();
	}

	return 0;
}