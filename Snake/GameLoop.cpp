#include "GameLoop.h"
#include "UserInputHandler.h"
#include "GameObjectInstantiator.h"
#include <iostream>

GameLoop::GameLoop(GameObjectStore& gameObjectStore,
	const GameSettings& gameSettings,
	Renderer& renderer,
	CollisionSystem& collisionSystem,
	sf::RenderWindow& renderWindow)
	:
	lag{},
	clock{},
	fixedTimeStep{ gameSettings.getFixedTimeStep() },
	gameObjectStore{gameObjectStore},
	renderer{ renderer },
	collisionSystem{ collisionSystem },
	renderWindow{ renderWindow }
{
	awake();
}

void GameLoop::awake()
{
	for (auto& e : gameObjectStore.getGameObjects())
	{
		e->awake();
	}
}

void GameLoop::execute()
{
	lag += clock.restart();
	handleUserInput();
	update();
	while (lag >= fixedTimeStep)
	{
		checkCollisions();
		fixedUpdate();
		lag -= fixedTimeStep;
	}
	render();
	destroySelectedGameObjects();
}

void GameLoop::update()
{
	const auto& size = gameObjectStore.getGameObjects().size();
	const auto& gameObjects = gameObjectStore.getGameObjects();
	for (size_t i{}; i < size; ++i)
	{
		gameObjects[i]->update();
	}
}

void GameLoop::fixedUpdate()
{
	const auto& size = gameObjectStore.getGameObjects().size();
	const auto& gameObjects = gameObjectStore.getGameObjects();
	for (size_t i{}; i < size; ++i)
	{
		gameObjects[i]->fixedUpdate();
	}
}

void GameLoop::handleUserInput()
{
	KeyHandler::update();
	UserInputHandler::update();
}

void GameLoop::render() const
{
	renderer.render(renderWindow);
}

void GameLoop::checkCollisions() const
{
	collisionSystem.checkCollisions();
}

void GameLoop::destroySelectedGameObjects()
{
	GameObjectInstantiator::destroy();
}
