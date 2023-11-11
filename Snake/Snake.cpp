#include "Snake.h"
#include "WorldDirection.h"
#include "UserInputHandler.h"

void Snake::update()
{
	if (UserInputHandler::upPressed())
	{
	}
	if (UserInputHandler::downPressed())
	{
	}
	if (UserInputHandler::rightPressed())
	{
	}
	if (UserInputHandler::leftPressed())
	{
	}
}

void Snake::fixedUpdate()
{
}

void Snake::onEnterCollision(GameObject& gameObject)
{
}

void Snake::turn(sf::Vector2f direction)
{

}

void Snake::move()
{
}
