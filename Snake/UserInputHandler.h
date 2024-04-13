#pragma once
#include <SFML/Window/Keyboard.hpp>
#include "KeyHandler.h"

class UserInputHandler
{
public:
	static void update();
	static bool upPressed() noexcept;
	static bool downPressed() noexcept;
	static bool rightPressed() noexcept;
	static bool leftPressed() noexcept;
private:
	static bool upPressedState;
	static bool downPressedState;
	static bool rightPressedState;
	static bool leftPressedState;
};

