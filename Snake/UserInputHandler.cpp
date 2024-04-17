#include "UserInputHandler.h"
#include "WorldDirection.h"

bool UserInputHandler::upPressedState = false;
bool UserInputHandler::downPressedState = false;
bool UserInputHandler::rightPressedState = false;
bool UserInputHandler::leftPressedState = false;
sf::Vector2f UserInputHandler::latestDirection = {};

void UserInputHandler::update()
{
	upPressedState = KeyHandler::wasKeyPressed(sf::Keyboard::Up);
	downPressedState = KeyHandler::wasKeyPressed(sf::Keyboard::Down);
	rightPressedState = KeyHandler::wasKeyPressed(sf::Keyboard::Right);
	leftPressedState = KeyHandler::wasKeyPressed(sf::Keyboard::Left);
	updateLatestDirection();
}

bool UserInputHandler::upPressed() noexcept
{
	return upPressedState;
}

bool UserInputHandler::downPressed() noexcept
{
	return downPressedState;
}

bool UserInputHandler::rightPressed() noexcept
{
	return rightPressedState;
}

bool UserInputHandler::leftPressed() noexcept
{
	return leftPressedState;
}

sf::Vector2f& UserInputHandler::getLatestDirection() noexcept
{
	return latestDirection;
}

void UserInputHandler::resetLatestDirection() noexcept
{
	latestDirection = {};
}

void UserInputHandler::updateLatestDirection() noexcept
{
	if (UserInputHandler::upPressed())
	{
		latestDirection = WorldDirection::up;
	}
	if (UserInputHandler::downPressed())
	{
		latestDirection = WorldDirection::down;
	}
	if (UserInputHandler::rightPressed())
	{
		latestDirection = WorldDirection::right;
	}
	if (UserInputHandler::leftPressed())
	{
		latestDirection = WorldDirection::left;
	}
}
