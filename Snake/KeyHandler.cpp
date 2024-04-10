#include "KeyHandler.h"

std::map<sf::Keyboard::Key, bool> KeyHandler::keyPreviousStates = {};
std::map<sf::Keyboard::Key, bool> KeyHandler::keyStates = {};
std::vector<sf::Keyboard::Key> KeyHandler::keys = { sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Right, sf::Keyboard::Left };

void KeyHandler::initialize() noexcept
{
	for (auto& key : keys)
	{
		keyStates[key] = false;
		keyPreviousStates[key] = false;
	}
}

bool KeyHandler::wasKeyPressed(sf::Keyboard::Key key) noexcept
{
	return keyStates[key];
}

void KeyHandler::update() noexcept
{
	bool currentState{};

	for (auto& key : keys)
	{
		currentState = sf::Keyboard::isKeyPressed(key);

		if (!currentState)
		{
			keyStates[key] = false;
			keyPreviousStates[key] = false;
			continue;
		}

		if (currentState && !keyPreviousStates[key])
		{
			keyStates[key] = true;
			keyPreviousStates[key] = true;
			continue;
		}

		if (currentState && keyPreviousStates[key])
		{
			keyStates[key] = false;
		}
	}

}
