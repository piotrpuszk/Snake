#include "GameLoop.h"
#include "UserInputHandler.h"

GameLoop::GameLoop(const GameSettings& gameSettings,
	Renderer& renderer,
	CollisionSystem& collisionSystem,
	sf::RenderWindow& renderWindow)
	:
	lag{},
	clock{},
	fixedTimeStep{ gameSettings.getFixedTimeStep() },
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

}

void GameLoop::fixedUpdate()
{
	
}

void GameLoop::handleUserInput()
{
	UserInputHandler::update();
}

void GameLoop::render()
{
	renderer.render(renderWindow);
}

void GameLoop::collisionCheck()
{
	collisionSystem.checkCollisions();
}
