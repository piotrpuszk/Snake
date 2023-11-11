#pragma once
#include "GameSettings.h"
#include "Renderer.h"
#include "CollisionSystem.h"


class GameLoop
{
public:
	GameLoop(const GameSettings& gameSettings, 
		Renderer& renderer,
		CollisionSystem& collisionSystem, 
		sf::RenderWindow& renderWindow);

	void execute();
private:
	void update();
	void fixedUpdate();
	void handleUserInput();
	void render();
	void collisionCheck();

	sf::Time lag;
	sf::Time fixedTimeStep;
	sf::Clock clock;
	Renderer& renderer;
	CollisionSystem& collisionSystem;
	sf::RenderWindow& renderWindow;
};

