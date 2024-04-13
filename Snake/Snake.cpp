#include "Snake.h"
#include "UserInputHandler.h"
#include "WorldDirection.h"
#include "GameObjectInstantiator.h"
#include "Maths.h"
#include <cmath>
#include <iostream>

Snake::Snake()
	:
	turnPoints{}
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

	turnPoints.insert(begin(turnPoints), TurnPoint{ transform->getPosition(), transform->getForward(), direction });
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
	auto headPosition{ transform->getPosition() };
	auto size{ 20.f };
	auto forward{ transform->getForward() };
	auto position{ headPosition };
	size_t tileIndex{ 1 };
	meshRenderers[0]->updatePosition(position);
	vector<TurnPoint> turnPointsToErase{};

	for (size_t turnPointIndex{}; turnPointIndex < turnPoints.size(); ++turnPointIndex)
	{
		auto turnPoint{ turnPoints[turnPointIndex] };

		if (tileIndex >= meshRenderers.size())
		{
			for_each(begin(turnPoints) + turnPointIndex, end(turnPoints), [&](const auto& e) { turnPointsToErase.push_back(e); });
			break;
		}

		forward = turnPoint.getDirectionTo();
		const auto distance{ Maths::magnitude(position - turnPoint.getPosition()) };
		const auto numberOfTiles{ floor(distance / size) };
		for (size_t i{}; i < numberOfTiles && tileIndex + i < meshRenderers.size(); ++i)
		{
			position -= size * forward;
			meshRenderers[tileIndex + i]->updatePosition(position);
		}
		tileIndex += numberOfTiles;

		if (tileIndex >= meshRenderers.size())
		{
			for_each(begin(turnPoints) + turnPointIndex, end(turnPoints), [&](const auto& e) { turnPointsToErase.push_back(e); });
			break;
		}

		auto remainder{ abs(distance - numberOfTiles * size) };

		if (remainder <= 0)
		{
			forward = turnPoint.getDirectionFrom();
			continue;
		}

		float availableDistance{ size };
		for (size_t j{ turnPointIndex }; j < turnPoints.size(); ++j)
		{
			auto currentTurnPoint{ turnPoints[j] };
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

	for (; tileIndex < meshRenderers.size(); ++tileIndex)
	{
		position -= size * forward;
		meshRenderers[tileIndex]->updatePosition(position);
	}

	for (const auto& turnPoint : turnPointsToErase)
	{
		eraseTurnPoint(turnPoint);
	}
}

void Snake::eraseTurnPoint(TurnPoint turnPoint)
{
	erase(turnPoints, turnPoint);
}
