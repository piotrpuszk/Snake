#include "GameLoop.h"
#include "UserInputHandler.h"

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
}

void GameLoop::execute()
{
	lag += clock.restart();
	handleUserInput();
	update();
	while (lag >= fixedTimeStep)
	{
		fixedUpdate();
		lag -= fixedTimeStep;
	}
	render();
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

void GameLoop::render()
{
	for (auto& go : gameObjectStore.getGameObjects())
	{
		auto transform = go->getComponent<Transform>();
		auto meshRenderer = go->getComponent<MeshRenderer>();
		if (transform && meshRenderer)
		{
			meshRenderer->updatePosition(transform->getPosition());
		}
	}

	renderer.render(renderWindow);
}

void GameLoop::collisionCheck()
{
	collisionSystem.checkCollisions();
}
