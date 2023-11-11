#include "UserInputHandler.h"

bool UserInputHandler::upPressedState = false;
bool UserInputHandler::downPressedState = false;
bool UserInputHandler::rightPressedState = false;
bool UserInputHandler::leftPressedState = false;

void UserInputHandler::update()
{
	UserInputHandler::upPressedState = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	UserInputHandler::downPressedState = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	UserInputHandler::rightPressedState = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
	UserInputHandler::leftPressedState = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
}

bool UserInputHandler::upPressed()
{
	return UserInputHandler::upPressedState;
}

bool UserInputHandler::downPressed()
{
	return UserInputHandler::downPressedState;
}

bool UserInputHandler::rightPressed()
{
	return UserInputHandler::rightPressedState;
}

bool UserInputHandler::leftPressed()
{
	return UserInputHandler::leftPressedState;
}

