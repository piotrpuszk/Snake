#include "SnakeMovement.h"

SnakeMovement::SnakeMovement( float speed)
	:
	speed{ speed }
{
	transform = getComponent<Transform>();
}

void SnakeMovement::move()
{
	transform->setPosition(transform->getPosition() + transform->getForward());
}

void SnakeMovement::turn(sf::Vector2f direction)
{
	transform->setForward(direction);
}

float SnakeMovement::getSpeed() const noexcept
{
	return speed;
}

void SnakeMovement::setSpeed(float value) noexcept
{
	speed = value;
}
