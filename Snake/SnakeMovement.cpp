#include "SnakeMovement.h"
#include <cmath>
#include "Orientation.h"
#include "Maths.h"

SnakeMovement::SnakeMovement(Transform* transform, float speed, float elementSize)
	:
	transform{ transform },
	speed{ speed },
	elementSize{ elementSize },
	elementSizeSquared{ elementSize * elementSize }
{
}

void SnakeMovement::move()
{
	auto newPosition{ transform->getPosition() + speed * transform->getForward() };
	transform->setPosition(newPosition);
}

void SnakeMovement::turn(const sf::Vector2f& direction)
{
	const auto& orientations{Orientation::getOrientation(direction)};
	transform->setLeft(orientations[0]);
	transform->setForward(orientations[1]);
	transform->setRight(orientations[2]);
}

float SnakeMovement::getSpeed() const noexcept
{
	return speed;
}

void SnakeMovement::setSpeed(float value) noexcept
{
	speed = value;
}

bool SnakeMovement::canTurn(const sf::Vector2f& direction, const std::vector<TurnPoint>& turnPoints) const noexcept
{
	if (direction.x == 0.f && direction.y == 0.f)
	{
		return false;
	}

	const auto& currentDirection{ transform->getForward() };

	if (turnPoints.empty())
	{
		return !WorldDirection::areOppositeDirections(currentDirection, direction);
	}

	const auto& currentPosition{ transform->getPosition() };
	const auto& latestTurnPointPosition{ turnPoints[0].getPosition() };
	const auto& distanceToLatestTurnPointSquared{ Maths::magnitudeSquared(currentPosition - latestTurnPointPosition) };

	return distanceToLatestTurnPointSquared > elementSizeSquared && !WorldDirection::areOppositeDirections(currentDirection, direction);
}
