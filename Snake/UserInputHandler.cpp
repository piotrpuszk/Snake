#include "UserInputHandler.h"

bool UserInputHandler::upPressedState = false;
bool UserInputHandler::downPressedState = false;
bool UserInputHandler::rightPressedState = false;
bool UserInputHandler::leftPressedState = false;

void UserInputHandler::update()
{
	UserInputHandler::upPressedState = KeyHandler::wasKeyPressed(sf::Keyboard::Up);
	UserInputHandler::downPressedState = KeyHandler::wasKeyPressed(sf::Keyboard::Down);
	UserInputHandler::rightPressedState = KeyHandler::wasKeyPressed(sf::Keyboard::Right);
	UserInputHandler::leftPressedState = KeyHandler::wasKeyPressed(sf::Keyboard::Left);
}

bool UserInputHandler::upPressed() noexcept
{
	return UserInputHandler::upPressedState;
}

bool UserInputHandler::downPressed() noexcept
{
	return UserInputHandler::downPressedState;
}

bool UserInputHandler::rightPressed() noexcept
{
	return UserInputHandler::rightPressedState;
}

bool UserInputHandler::leftPressed() noexcept
{
	return UserInputHandler::leftPressedState;
}

