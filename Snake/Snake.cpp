#include "Snake.h"
#include "UserInputHandler.h"
#include <iostream>
#include "WorldDirection.h"
#include "GameObjectInstantiator.h"

Snake::Snake(vector<shared_ptr<SnakePart>> parts)
	:
	parts{ parts }
{
}

void Snake::awake()
{
	auto tail{ *std::find_if(begin(parts), end(parts), [](const auto& part) {return part.get()->isTail(); }) };

	auto lambda = [this](TurnPoint turnPoint)
		{
			auto snakePartWorkaroundToDelete
			{
				*std::find_if(
					begin(turnPointWorkarounds),
					end(turnPointWorkarounds), 
					[&](const auto& snakePart)
					{
						return snakePart.get()->getTransform().getPosition() == turnPoint.getPosition();
					}
				)
			};
			GameObjectInstantiator::destroy(snakePartWorkaroundToDelete);
		};

	tail.get()->setOnTurnPointDeleted(lambda);
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

	TurnPoint turnPoint{ parts[0].get()->getTransform().getPosition(), direction };

	parts[0].get()->turn(direction);

	for (size_t i = 1; i < parts.size(); i++)
	{
		parts[i].get()->addTurnPoint(turnPoint);
	}

	auto snakePart{ GameObjectInstantiator::instantiate<SnakePart>(parts[0].get()->getComponent<BoxCollider>()->getSize()) };
	snakePart.get()->getTransform().setPosition(turnPoint.getPosition());
	turnPointWorkarounds.push_back(snakePart);
}

void Snake::move()
{
	for (auto& part : parts)
	{
		part.get()->move();
	}
}

void Snake::onEatFruit()
{
}

void Snake::grow(int amount)
{
}

bool Snake::canTurn(sf::Vector2f direction) const noexcept
{
	auto currentDirection{ parts[0].get()->getTransform().getForward() };

	return !WorldDirection::areOppositeDirections(currentDirection, direction);
}
