#include "GeneratorOfSnakePartPositions.h"
#include "Maths.h"
#include <iostream>

GeneratorOfSnakePartPositions::GeneratorOfSnakePartPositions(TurnPointStore* turnPointStore, size_t positionCount, float elementSize)
	:
	turnPointStore{ turnPointStore },
	positionCount{ positionCount },
	elementSize{ elementSize },
	currentPosition{},
	currentForward{},
	positions{}
{
}

void GeneratorOfSnakePartPositions::increasePositionCount()
{
	++positionCount;
}

std::vector<sf::Vector2f> GeneratorOfSnakePartPositions::getPositions(sf::Vector2f startPosition, sf::Vector2f forward)
{
	currentForward = forward;
	currentPosition = startPosition;
	positions = { currentPosition };
	const auto& turnPoints = turnPointStore->getTurnPoints();

	for (turnPointIterator = std::begin(turnPoints); turnPointIterator != std::end(turnPoints); ++turnPointIterator)
	{
		addFromCurrentPositionToTurnPoint();
		addAtTurnPoint();
		if (turnPointIterator == std::end(turnPoints))
		{
			break;
		}
	}

	addAfterTurnPoints();

	return std::vector(std::begin(positions), std::begin(positions) + positionCount);
}

void GeneratorOfSnakePartPositions::addFromCurrentPositionToTurnPoint()
{
	currentForward = turnPointIterator->getDirectionTo();
	const auto distance{ Maths::magnitude(currentPosition - turnPointIterator->getPosition()) };
	const auto numberOfTiles{ floor(distance / elementSize) };

	for (size_t i{}; i < numberOfTiles; ++i)
	{
		currentPosition -= elementSize * currentForward;
		positions.push_back(currentPosition);
	}

	const auto remainingDistance{ distance - numberOfTiles * elementSize };

	if (remainingDistance <= 0)
	{
		currentForward = turnPointIterator->getDirectionFrom();
	}
}

void GeneratorOfSnakePartPositions::addAtTurnPoint()
{
	auto availableDistance{ elementSize };

	for (auto turnPoint = turnPointIterator; turnPoint != std::end(turnPointStore->getTurnPoints()); ++turnPoint)
	{
		const auto distanceBetween{ Maths::magnitude(currentPosition - turnPoint->getPosition()) };

		if (distanceBetween > availableDistance)
		{
			currentForward = turnPoint->getDirectionTo();
			--turnPointIterator;
			break;
		}
		availableDistance -= distanceBetween;
		currentPosition = turnPoint->getPosition();
		currentForward = turnPoint->getDirectionFrom();
		++turnPointIterator;
	}

	if (availableDistance > 0)
	{
		currentPosition -= availableDistance * currentForward;
	}

	positions.push_back(currentPosition);
}

void GeneratorOfSnakePartPositions::addAfterTurnPoints()
{
	for (size_t i{}; i < positionCount; ++i)
	{
		currentPosition -= elementSize * currentForward;
		positions.push_back(currentPosition);
	}
}