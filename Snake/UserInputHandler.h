#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>
#include "KeyHandler.h"

class UserInputHandler
{
public:
	static void update();
	static bool upPressed() noexcept;
	static bool downPressed() noexcept;
	static bool rightPressed() noexcept;
	static bool leftPressed() noexcept;
	static sf::Vector2f& getLatestDirection() noexcept;
	static void resetLatestDirection() noexcept;
private:
	static void updateLatestDirection() noexcept;
	
	static bool upPressedState;
	static bool downPressedState;
	static bool rightPressedState;
	static bool leftPressedState;
	static sf::Vector2f latestDirection;
};

