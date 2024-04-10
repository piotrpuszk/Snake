#pragma once
#include <map>
#include <vector>
#include <SFML/Window/Keyboard.hpp>

class KeyHandler
{
public:
	static void initialize() noexcept;
	static bool wasKeyPressed(sf::Keyboard::Key key) noexcept;
	static void update() noexcept;
private:
	static std::map<sf::Keyboard::Key, bool> keyStates;
	static std::map<sf::Keyboard::Key, bool> keyPreviousStates;
	static std::vector<sf::Keyboard::Key> keys;
};

