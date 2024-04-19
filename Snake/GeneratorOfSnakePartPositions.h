#pragma once
#include <memory>
#include "TurnPointStore.h"
#include "Component.h"
#include <tuple>

class GeneratorOfSnakePartPositions : public Component
{
public:
	GeneratorOfSnakePartPositions(TurnPointStore* turnPointStore, size_t positionCount, float elementSize);

	void increasePositionCount();
	std::vector<std::tuple<sf::Vector2f, float>> getPositions(sf::Vector2f startPosition, sf::Vector2f forward);
private:
	void addFromCurrentPositionToTurnPoint();
	void addAtTurnPoint();
	void addAfterTurnPoints();

	TurnPointStore* turnPointStore;
	size_t positionCount;
	float elementSize;
	sf::Vector2f currentPosition;
	sf::Vector2f currentForward;
	std::vector<std::tuple<sf::Vector2f, float>> positions;
	std::vector<TurnPoint>::const_iterator turnPointIterator;
};

