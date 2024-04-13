#include "SnakeComponentPositionIterator.h"
#include "Maths.h"

SnakeComponentPositionIterator::SnakeComponentPositionIterator(TurnPointStore* turnPointStore, size_t positionCount, float elementSize)
	:
	turnPointStore{ turnPointStore },
	positionCount{ positionCount },
	elementSize{ elementSize },
	position{},
	forward{},
	positionCounter{}
{
}

std::vector<sf::Vector2f> SnakeComponentPositionIterator::getPositions(sf::Vector2f startPosition, sf::Vector2f forward)
{
	this->forward = forward;
	position = startPosition;
	positionCounter = positionCount;
	std::vector<sf::Vector2f> result{ position };

	for (size_t turnPointIndex{}; turnPointIndex < turnPointStore->getTurnPoints().size(); ++turnPointIndex)
	{
		for (const auto& e : getPositionsToTurnPoint(turnPointIndex))
		{
			result.push_back(e);
		}
		position = result[result.size() - 1];
	}

	for (auto& e : getPositionsAfterTurnPoint())
	{
		result.push_back(e);
	}

	return std::vector(std::begin(result), std::begin(result) + positionCount);
}

std::vector<sf::Vector2f> SnakeComponentPositionIterator::getPositionsToTurnPoint(size_t& turnPointIndex)
{
	forward = turnPointStore->getTurnPoints()[turnPointIndex].getDirectionTo();
	const auto distance{ Maths::magnitude(position - turnPointStore->getTurnPoints()[turnPointIndex].getPosition()) };
	const auto numberOfTiles{ floor(distance / elementSize) };
	std::vector<sf::Vector2f> positions;

	for (size_t i{}; i < numberOfTiles; ++i)
	{
		position -= elementSize * forward;
		positions.push_back(position);
		onPositionAdded(turnPointIndex);
	}


	auto remainingDistance{ distance - numberOfTiles * elementSize };

	if (remainingDistance <= 0)
	{
		forward = turnPointStore->getTurnPoints()[turnPointIndex].getDirectionFrom();
		return positions;
	}

	positions.push_back(getRemainingPositionToTurnPoint(turnPointIndex));
	onPositionAdded(turnPointIndex);

	return positions;
}

sf::Vector2f SnakeComponentPositionIterator::getRemainingPositionToTurnPoint(size_t& turnPointIndex)
{
	float availableDistance{ elementSize };

	for (size_t j{ turnPointIndex }; j < turnPointStore->getTurnPoints().size(); ++j)
	{
		auto currentTurnPoint{ turnPointStore->getTurnPoints()[j] };
		auto distanceBetween{ Maths::magnitude(position - currentTurnPoint.getPosition()) };
		if (distanceBetween > availableDistance)
		{
			forward = currentTurnPoint.getDirectionTo();
			--turnPointIndex;
			break;
		}
		availableDistance -= distanceBetween;
		position = currentTurnPoint.getPosition();
		forward = currentTurnPoint.getDirectionFrom();
		++turnPointIndex;
	}
	if (availableDistance > 0)
	{
		position -= availableDistance * forward;
	}
	return position;
}

std::vector<sf::Vector2f> SnakeComponentPositionIterator::getPositionsAfterTurnPoint()
{
	std::vector<sf::Vector2f> result{};

	for (size_t i{}; i < positionCount; ++i)
	{
		position -= elementSize * forward;
		result.push_back(position);
	}
	return result;
}

void SnakeComponentPositionIterator::updateTurnPointsMarkedForRemoval(size_t& turnPointIndex)
{
	if (positionCounter <= 0)
	{
		turnPointStore->markForRemoval(turnPointStore->getTurnPoints(), turnPointIndex);
	}
}

void SnakeComponentPositionIterator::onPositionAdded(size_t turnPointIndex)
{
	--positionCounter;
	updateTurnPointsMarkedForRemoval(turnPointIndex);
}
