#include "SnakeMovement.h"
#include <cmath>

SnakeMovement::SnakeMovement(Transform* transform, float speed)
	:
	transform{ transform },
	speed{ speed }
{
}

void SnakeMovement::move()
{
	auto newPosition{ transform->getPosition() + speed * transform->getForward() };
	newPosition.x = std::round(newPosition.x);
	newPosition.y = std::round(newPosition.y);
	transform->setPosition(newPosition);
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
