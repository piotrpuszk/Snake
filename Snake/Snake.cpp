#include "Snake.h"
#include "UserInputHandler.h"
#include "WorldDirection.h"
#include "GameObjectInstantiator.h"
#include "Maths.h"
#include <cmath>
#include <iostream>

Snake::Snake(TurnPointStore turnPointStore, float partSize)
	:
	turnPointStore{ turnPointStore },
	partSize{ partSize }
{
}

void Snake::awake()
{
	meshRenderers = getComponents<MeshRenderer>();
	snakeMovement = getComponent<SnakeMovement>();
	transform = getComponent<Transform>();
}

void Snake::update()
{
	if (UserInputHandler::upPressed())
	{
		turn(WorldDirection::up);
	}
	if (UserInputHandler::downPressed())
	{
		turn(WorldDirection::down);
	}
	if (UserInputHandler::rightPressed())
	{
		turn(WorldDirection::right);
	}
	if (UserInputHandler::leftPressed())
	{
		turn(WorldDirection::left);
	}
}

void Snake::fixedUpdate()
{
	move();
	updateMeshRendererPositions();
}

void Snake::onEnterCollision(GameObject& gameObject)
{
}

void Snake::turn(sf::Vector2f direction)
{
	if (!canTurn(direction))
	{
		return;
	}

	turnPointStore.add(TurnPoint{ transform->getPosition(), transform->getForward(), direction });
	snakeMovement->turn(direction);
}

void Snake::move()
{
	snakeMovement->move();
}

void Snake::onEatFruit()
{
}

void Snake::grow(int amount)
{
}

bool Snake::canTurn(sf::Vector2f direction) const noexcept
{
	auto currentDirection{ transform->getForward() };
	return !WorldDirection::areOppositeDirections(currentDirection, direction);
}

void Snake::updateMeshRendererPositions()
{
	auto forward{ transform->getForward() };
	auto position{ transform->getPosition() };
	size_t tileIndex{ 1 };
	meshRenderers[0]->updatePosition(position);

	for (size_t turnPointIndex{}; turnPointIndex < turnPointStore.getTurnPoints().size(); ++turnPointIndex)
	{
		if (tileIndex >= meshRenderers.size())
		{
			turnPointStore.markForRemoval(turnPointStore.getTurnPoints(), turnPointIndex);
			break;
		}

		fillInDistanceToTurnPoint(turnPointIndex, tileIndex, forward, position);
	}

	fillInDistanceAfterTurnPoints(position, forward, tileIndex);
	turnPointStore.removeMarked();
}

void Snake::fillInDistanceToTurnPoint(size_t& turnPointIndex, size_t& tileIndex, sf::Vector2f& forward, sf::Vector2f& position)
{
	forward = turnPointStore.getTurnPoints()[turnPointIndex].getDirectionTo();
	const auto distance{ Maths::magnitude(position - turnPointStore.getTurnPoints()[turnPointIndex].getPosition())};
	const auto numberOfTiles{ floor(distance / partSize) };
	for (size_t i{}; i < numberOfTiles && tileIndex + i < meshRenderers.size(); ++i)
	{
		position -= partSize * forward;
		meshRenderers[tileIndex + i]->updatePosition(position);
	}
	tileIndex += numberOfTiles;

	auto remainingDistance{ abs(distance - numberOfTiles * partSize) };

	if (remainingDistance <= 0)
	{
		forward = turnPointStore.getTurnPoints()[turnPointIndex].getDirectionFrom();
		return;
	}

	if (tileIndex >= meshRenderers.size())
	{
		return;
	}

	fillInRemainingDistanceToTurnPoint(turnPointIndex, tileIndex, position, forward);
}

void Snake::fillInRemainingDistanceToTurnPoint(size_t& turnPointIndex, size_t& tileIndex, sf::Vector2f& position, sf::Vector2f& forward)
{
	float availableDistance{ partSize };
	for (size_t j{ turnPointIndex }; j < turnPointStore.getTurnPoints().size(); ++j)
	{
		auto currentTurnPoint{ turnPointStore.getTurnPoints()[j] };
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
	meshRenderers[tileIndex]->updatePosition(position);
	tileIndex++;
}

void Snake::fillInDistanceAfterTurnPoints(sf::Vector2f& position, sf::Vector2f& forward, size_t& tileIndex)
{
	for (; tileIndex < meshRenderers.size(); ++tileIndex)
	{
		position -= partSize * forward;
		meshRenderers[tileIndex]->updatePosition(position);
	}
}
