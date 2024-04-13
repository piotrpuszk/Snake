#pragma once
#include <memory>
#include "TurnPointStore.h"
class GeneratorOfSnakePartPositions
{
public:
	GeneratorOfSnakePartPositions(TurnPointStore* turnPointStore, size_t positionCount, float elementSize);

	void increasePositionCount();
	std::vector<sf::Vector2f> getPositions(sf::Vector2f startPosition, sf::Vector2f forward);
private:
	void addFromCurrentPositionToTurnPoint();
	void addAtTurnPoint();
	void addAfterTurnPoints();

	TurnPointStore* turnPointStore;
	size_t positionCount;
	float elementSize;
	sf::Vector2f currentPosition;
	sf::Vector2f currentForward;
	std::vector<sf::Vector2f> positions;
	std::vector<TurnPoint>::const_iterator turnPointIterator;
};

