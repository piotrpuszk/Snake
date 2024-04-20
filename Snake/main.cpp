#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <initializer_list>
#include "GameObjectFactory.h"
#include "Renderer.h"
#include "GameSettings.h"
#include "CollisionSystem.h"
#include "GameLoop.h"
#include "GameObjectStore.h"
#include "KeyHandler.h"
#include "GameObjectInstantiator.h"
#include "WorldDirection.h"

GameSettings getGameSettings();
std::vector<Wall*> createWalls(const GameSettings&, GameObjectFactory&);
CollisionSystem createCollisionSystem(Snake*&, const std::vector<Wall*>&);
void initializeGameObjectInstantiator(GameObjectFactory&, GameObjectStore&, CollisionSystem&);
ConsumablesSpawner* createConsumablesSpawner(const GameSettings& settings, GameObjectFactory& gameObjectFactory);

int main()
{
	const auto settings = getGameSettings();
	sf::RenderWindow window(sf::VideoMode(settings.getMapSize().x, settings.getMapSize().y), "My window", settings.getWindowStyle());
	
	TextureStore textureStore{};
	GameObjectStore gameObjectStore{};
	GameObjectFactory gameObjectFactory{ textureStore, gameObjectStore, settings };

	auto snake{ gameObjectFactory.create<Snake>() };
	std::vector<Wall*> walls = createWalls(settings, gameObjectFactory);
	CollisionSystem collisionSystem = createCollisionSystem(snake, walls);
	createConsumablesSpawner(settings, gameObjectFactory);
	auto backgroundTexture{ gameObjectFactory.create<BackgroundTexture>() };

	initializeGameObjectInstantiator(gameObjectFactory, gameObjectStore, collisionSystem);

	Renderer renderer{ gameObjectStore };
	GameLoop gameLoop{ gameObjectStore, settings, renderer, collisionSystem, window };

	
	
	KeyHandler::initialize();

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

GameSettings getGameSettings()
{
	return GameSettings{}.setFixedTimeStep(sf::seconds(0.02f))
		.setMapSize({ 1920, 1080 })
		.setWallSize(50.f)
		.setAdditionalMargin(50.f)
		.setInitialSpawnConsumablesInterval(sf::seconds(2.f))
		.setWindowStyle(sf::Style::Fullscreen)
		.setSnakePartSize(20.f)
		.setInitialSnakePartCount(10)
		.setInitialSnakeForward({ 1.f, 0.f })
		.setInitialSnakePosition({ 300.f, 150.f })
		.setInitialSnakeSpeed(5.f)
		.setBackgroundRenderPriority(-1000)
		.setGameOverRenderPriority(1000)
		.setTurnPointRenderPriority(1);
}

std::vector<Wall*> createWalls(const GameSettings& settings, GameObjectFactory& gameObjectFactory)
{
	const auto& map{ settings.getMapSize2f() };
	const float wallSize{ settings.getWallSize() };
	return
	{
		gameObjectFactory.create<Wall>(sf::Vector2f{0, 0}, WorldDirection::down, map.y / wallSize, wallSize, sf::Vector2f{wallSize * 0.5f, map.y * 0.5f}, sf::Vector2f{wallSize, map.y}),
		gameObjectFactory.create<Wall>(sf::Vector2f{map.x - wallSize, 0},WorldDirection::down, map.y / wallSize, wallSize, sf::Vector2f{map.x - wallSize * 0.5f, map.y * 0.5f}, sf::Vector2f{wallSize, map.y}),
		gameObjectFactory.create<Wall>(sf::Vector2f{0, 0}, WorldDirection::right, map.x / wallSize, wallSize, sf::Vector2f{map.x * 0.5f, wallSize * 0.5f}, sf::Vector2f{map.x, wallSize}),
		gameObjectFactory.create<Wall>(sf::Vector2f{0, map.y - wallSize}, WorldDirection::right, map.x / wallSize, wallSize, sf::Vector2f{map.x * 0.5f, map.y - wallSize * 0.5f}, sf::Vector2f{map.x, wallSize}),
	};
}

CollisionSystem createCollisionSystem(Snake*& snake, const std::vector<Wall*>& walls)
{
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
	return collisionSystem;
}

void initializeGameObjectInstantiator(GameObjectFactory& gameObjectFactory, GameObjectStore& gameObjectStore, CollisionSystem& collisionSystem)
{
	GameObjectInstantiator::setGameObjectFactory(&gameObjectFactory);
	GameObjectInstantiator::setGameObjectStore(&gameObjectStore);
	GameObjectInstantiator::setCollisionSystem(&collisionSystem);
}

ConsumablesSpawner* createConsumablesSpawner(const GameSettings& settings, GameObjectFactory& gameObjectFactory)
{
	return gameObjectFactory.create<ConsumablesSpawner>(settings.getMapSize2f() * 0.5f,
		sf::Vector2f{ settings.getMapSize2f().x - settings.getWallSize() * 2.f - settings.getAdditionalMargin(),
		settings.getMapSize2f().y - settings.getWallSize() * 2.f - settings.getAdditionalMargin() },
		settings.getInitialSpawnConsumablesInterval());
}
