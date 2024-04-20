#pragma once
#include <SFML/Graphics.hpp>

class GameSettings
{
public:
	GameSettings();

	GameSettings& setFixedTimeStep(sf::Time value);
	GameSettings& setMapSize(sf::Vector2u value);
	GameSettings& setWallSize(float value);
	GameSettings& setAdditionalMargin(float value);
	GameSettings& setInitialSpawnConsumablesInterval(sf::Time value);
	GameSettings& setWindowStyle(int value);
	GameSettings& setSnakePartSize(float value);
	GameSettings& setInitialSnakePartCount(size_t value);
	GameSettings& setInitialSnakeForward(sf::Vector2f value);
	GameSettings& setInitialSnakePosition(sf::Vector2f value);
	GameSettings& setInitialSnakeSpeed(float value);
	GameSettings& setBackgroundRenderPriority(int value);
	GameSettings& setGameOverRenderPriority(int value);
	GameSettings& setTurnPointRenderPriority(int value);

	const sf::Time getFixedTimeStep() const noexcept;
	const sf::Vector2u getMapSize() const noexcept;
	const sf::Vector2f getMapSize2f() const noexcept;
	const float getWallSize() const noexcept;
	const float getAdditionalMargin() const noexcept;
	const sf::Time getInitialSpawnConsumablesInterval() const noexcept;
	const int getWindowStyle() const noexcept;
	const float getSnakePartSize() const noexcept;
	const size_t getInitialSnakePartCount() const noexcept;
	const sf::Vector2f getInitialSnakeForward() const noexcept;
	const sf::Vector2f getInitialSnakePosition() const noexcept;
	const float getInitialSnakeSpeed() const noexcept;
	const int getBackgroundRenderPriority() const noexcept;
	const int getGameOverRenderPriority() const noexcept;
	const int getTurnPointRenderPriority() const noexcept;
private:
	sf::Time fixedTimeStep;
	sf::Vector2u mapSize;
	
	float wallSize;

	float additionalMargin;
	
	sf::Time initialSpawnConsumablesInterval;

	int windowStyle;

	float snakePartSize;
	size_t initialSnakePartCount;
	sf::Vector2f initialSnakeForward;
	sf::Vector2f initialSnakePosition;
	float initialSnakeSpeed;

	int backgroundRenderPriority;
	int gameOverRenderPriority;
	int turnPointRenderPriority;
}; 

