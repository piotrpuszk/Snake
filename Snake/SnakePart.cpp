#include "SnakePart.h"

SnakePart::SnakePart()
	:
	turnPoints{}
{
	snakeMovement = getComponent<SnakeMovement>();
	boxCollider = getComponent<BoxCollider>();
	transform = getComponent<Transform>();
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
	snakeMovement->move();
}

void SnakePart::turn(sf::Vector2f direction)
{
	snakeMovement->turn(direction);
}

void SnakePart::tryToUseTurnPoint()
{
	if (transform->getPosition() == turnPoints.front().getPosition())
	{
		transform->setForward(turnPoints.front().getDirection());
		turnPoints.pop();
	}
}

void SnakePart::addTurnPoint(TurnPoint turnPoint)
{
	turnPoints.emplace(turnPoint);
}
