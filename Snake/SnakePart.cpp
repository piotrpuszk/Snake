#include "SnakePart.h"
#include <iostream>

SnakePart::SnakePart()
	:
	turnPoints{},
	snakeMovement{},
	boxCollider{},
	transform{},
	meshRenderer{},
	isHeadInternal{},
	isTailInternal{}
{
}

void SnakePart::awake()
{
	snakeMovement = getComponent<SnakeMovement>();
	boxCollider = getComponent<BoxCollider>();
	transform = getComponent<Transform>();
	meshRenderer = getComponent<MeshRenderer>();
}

void SnakePart::update()
{
}

void SnakePart::fixedUpdate()
{
}

void SnakePart::onEnterCollision(GameObject& gameObject)
{
}

void SnakePart::move()
{
	tryToUseTurnPoint();
	snakeMovement->move();
}

void SnakePart::turn(sf::Vector2f direction)
{
	meshRenderer->rotate(Orientation::getAngle(transform->getForward(), direction));
	snakeMovement->turn(direction);
}

void SnakePart::tryToUseTurnPoint()
{
	while (!turnPoints.empty() && transform->getPosition() == turnPoints.front().getPosition())
	{

		turn(turnPoints.front().getDirection());
		if (isTail()) 
		{
			onTurnPointDeleted(turnPoints.front());
		}
		turnPoints.pop();
	}
}

void SnakePart::addTurnPoint(TurnPoint turnPoint)
{
	turnPoints.emplace(turnPoint);
}

Transform& SnakePart::getTransform() const
{
	return *transform;
}

void SnakePart::markAsHead()
{
	isHeadInternal = true;
}

void SnakePart::markAsTail()
{
	isTailInternal = true;
}

bool SnakePart::isHead() const noexcept
{
	return isHeadInternal;
}

bool SnakePart::isTail() const noexcept
{
	return isTailInternal;
}

void SnakePart::setOnTurnPointDeleted(std::function<void(TurnPoint)> onTurnPointDeleted)
{
	this->onTurnPointDeleted = onTurnPointDeleted;
}
