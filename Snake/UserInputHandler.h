#pragma once
#include <SFML/Window/Keyboard.hpp>
#include "KeyHandler.h"

class UserInputHandler
{
public:
	static void update();
	static bool upPressed();
	static bool downPressed();
	static bool rightPressed();
	static bool leftPressed();
private:
	static bool upPressedState;
	static bool downPressedState;
	static bool rightPressedState;
	static bool leftPressedState;
};

