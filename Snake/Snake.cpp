#include "Snake.h"
#include "UserInputHandler.h"
#include "WorldDirection.h"
#include "GameObjectInstantiator.h"
#include "Maths.h"
#include <cmath>

Snake::Snake(std::unique_ptr<TurnPointStore> turnPointStore, SnakeComponentPositionIterator snakeComponentPositionIterator)
	:
	turnPointStore{ std::move(turnPointStore) },
	snakeComponentPositionIterator{ snakeComponentPositionIterator },
	snakeMovement{},
	transform{},
	meshRenderers{},
	boxColliders{}
{
}

void Snake::awake()
{
	meshRenderers = getComponents<MeshRenderer>();
	boxColliders = getComponents<BoxCollider>();
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
	updateComponentsPositions();
	removeUsedUpTurnPoints();
	if (IsEatingItself())
	{
		GameObjectInstantiator::destroy(this);
	}
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

	turnPointStore->add(TurnPoint{ transform->getPosition(), transform->getForward(), direction });
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

void Snake::updateComponentsPositions()
{
	auto positions{ snakeComponentPositionIterator.getPositions(transform->getPosition(), transform->getForward()) };
	for (size_t i{}; i < positions.size(); i++)
	{
		meshRenderers[i]->setPosition(positions[i]);
		boxColliders[i]->setPosition(positions[i]);
	}
}

void Snake::removeUsedUpTurnPoints()
{
	turnPointStore->removeMarked();
}

bool Snake::IsEatingItself()
{
	auto head{ boxColliders[0] };

	for (size_t i{ 1 }; i < boxColliders.size(); i++)
	{
		auto other{ boxColliders[i] };


		if (head->isColliding(*other))
		{
			auto fromOtherToItself{ transform->getPosition() - other->getPosition() };
			if (Maths::dot(transform->getForward(), fromOtherToItself) < 0)
			{
				return true;
			}
		}
	}

	return false;
}