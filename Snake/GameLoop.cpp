#include "GameLoop.h"
#include "UserInputHandler.h"
#include "GameObjectInstantiator.h"

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
		collisionCheck();
		fixedUpdate();
		lag -= fixedTimeStep;
	}
	render();
	destroySelectedGameObjects();
}

void GameLoop::update()
{
	for (auto& go : gameObjectStore.getGameObjects())
	{
		go->update();
	}
}

void GameLoop::fixedUpdate()
{
	for (auto& go : gameObjectStore.getGameObjects())
	{
		go->fixedUpdate();
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

void GameLoop::collisionCheck() const
{
	collisionSystem.checkCollisions();
}

void GameLoop::destroySelectedGameObjects()
{
	GameObjectInstantiator::destroy();
}
