#include "GameSettings.h"

GameSettings::GameSettings()
	:
	fixedTimeStep{},
	mapSize{},
	wallSize{}
{
}

GameSettings& GameSettings::setFixedTimeStep(sf::Time value)
{
	fixedTimeStep = value;
	return *this;
}

GameSettings& GameSettings::setMapSize(sf::Vector2u value)
{
	mapSize = value;
	return *this;
}

GameSettings& GameSettings::setWallSize(float value)
{
	wallSize = value;
	return *this;
}

GameSettings& GameSettings::setAdditionalMargin(float value)
{
	additionalMargin = value;
	return *this;
}

GameSettings& GameSettings::setInitialSpawnConsumablesInterval(sf::Time value)
{
	initialSpawnConsumablesInterval = value;
	return *this;
}

GameSettings& GameSettings::setWindowStyle(int value)
{
	windowStyle = value;
	return *this;
}

GameSettings& GameSettings::setSnakePartSize(float value)
{
	snakePartSize = value;
	return *this;
}

GameSettings& GameSettings::setInitialSnakePartCount(size_t value)
{
	initialSnakePartCount = value;
	return *this;
}

GameSettings& GameSettings::setInitialSnakeForward(sf::Vector2f value)
{
	initialSnakeForward = value;
	return *this;
}

GameSettings& GameSettings::setInitialSnakePosition(sf::Vector2f value)
{
	initialSnakePosition = value;
	return *this;
}

GameSettings& GameSettings::setInitialSnakeSpeed(float value)
{
	initialSnakeSpeed = value;
	return *this;
}

GameSettings& GameSettings::setBackgroundRenderPriority(int value)
{
	backgroundRenderPriority = value;
	return *this;
}

GameSettings& GameSettings::setGameOverRenderPriority(int value)
{
	gameOverRenderPriority = value;
	return *this;
}

GameSettings& GameSettings::setTurnPointRenderPriority(int value)
{
	turnPointRenderPriority = value;
	return *this;
}

const sf::Time GameSettings::getFixedTimeStep() const noexcept
{
	return fixedTimeStep;
}

const sf::Vector2u GameSettings::getMapSize() const noexcept
{
	return mapSize;
}

const sf::Vector2f GameSettings::getMapSize2f() const noexcept
{
	return sf::Vector2f{ static_cast<float>(mapSize.x), static_cast<float>(mapSize.y) };
}

const float GameSettings::getWallSize() const noexcept
{
	return wallSize;
}

const float GameSettings::getAdditionalMargin() const noexcept
{
	return additionalMargin;
}

const sf::Time GameSettings::getInitialSpawnConsumablesInterval() const noexcept
{
	return initialSpawnConsumablesInterval;
}

const int GameSettings::getWindowStyle() const noexcept
{
	return windowStyle;
}

const float GameSettings::getSnakePartSize() const noexcept
{
	return snakePartSize;
}

const size_t GameSettings::getInitialSnakePartCount() const noexcept
{
	return initialSnakePartCount;
}

const sf::Vector2f GameSettings::getInitialSnakeForward() const noexcept
{
	return initialSnakeForward;
}

const sf::Vector2f GameSettings::getInitialSnakePosition() const noexcept
{
	return initialSnakePosition;
}

const float GameSettings::getInitialSnakeSpeed() const noexcept
{
	return initialSnakeSpeed;
}

const int GameSettings::getBackgroundRenderPriority() const noexcept
{
	return backgroundRenderPriority;
}

const int GameSettings::getGameOverRenderPriority() const noexcept
{
	return gameOverRenderPriority;
}

const int GameSettings::getTurnPointRenderPriority() const noexcept
{
	return turnPointRenderPriority;
}
