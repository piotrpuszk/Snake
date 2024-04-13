#pragma once
#include <memory>
#include "TurnPointStore.h"
class SnakeComponentPositionIterator
{
public:
	SnakeComponentPositionIterator(TurnPointStore* turnPointStore, size_t positionCount, float elementSize);
	std::vector<sf::Vector2f> getPositions(sf::Vector2f startPosition, sf::Vector2f forward);
private:
	std::vector<sf::Vector2f> getPositionsToTurnPoint(size_t& turnPointIndex);
	sf::Vector2f getRemainingPositionToTurnPoint(size_t& turnPointIndex);
	std::vector<sf::Vector2f> getPositionsAfterTurnPoint();
	void updateTurnPointsMarkedForRemoval(size_t& turnPointIndex);
	void onPositionAdded(size_t turnPointIndex);
	TurnPointStore* turnPointStore;
	size_t positionCount;
	size_t positionCounter;
	float elementSize;
	sf::Vector2f position;
	sf::Vector2f forward;
};

