#include "Snake.h"
#include "UserInputHandler.h"
#include "WorldDirection.h"
#include "GameObjectInstantiator.h"
#include "Maths.h"
#include <cmath>
#include <algorithm>
#include <iostream>

Snake::Snake(std::unique_ptr<TurnPointStore> turnPointStore, GeneratorOfSnakePartPositions generatorOfSnakePartPositions)
	:
	turnPointStore{ std::move(turnPointStore) },
	generatorOfSnakePartPositions{ generatorOfSnakePartPositions },
	snakeMovement{},
	transform{},
	meshRenderers{},
	boxColliders{}
{
	this->turnPointStore.get()->setRemoveMeshRenderer([this](auto e) {
		removeComponent(e);
		});
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
	const auto& positions = generatorOfSnakePartPositions.getPositions(transform->getPosition(), transform->getForward());
	updateComponentsPositions(positions);
	removeUsedUpTurnPoints(positions);
}

void Snake::onEnterCollision(GameObject* gameObject)
{
	if (isEatingItself())
	{
		GameObjectInstantiator::destroy(this);
	}

	if (isEatingFood(gameObject))
	{
		onEatFruit(dynamic_cast<Consumable*>(gameObject));
	}
}

void Snake::turn(sf::Vector2f direction)
{
	if (!canTurn(direction))
	{
		return;
	}
	auto meshRenderer{ addComponent<MeshRenderer>(meshRenderers[0]->getSprite()) };
	meshRenderer->setPosition(transform->getPosition());
	turnPointStore->add(TurnPoint{ transform->getPosition(), transform->getForward(), direction, meshRenderer });
	snakeMovement->turn(direction);
}

void Snake::move()
{
	snakeMovement->move();
}

void Snake::onEatFruit(Consumable* consumable)
{
	grow(consumable->getGrowSize());
}

void Snake::grow(int amount)
{
	for (size_t i = 0; i < amount; i++)
	{
		addComponent<MeshRenderer>(meshRenderers[0]->getSprite());
		addComponent<BoxCollider>(transform, transform->getPosition(), boxColliders[0]->getSize());
		generatorOfSnakePartPositions.increasePositionCount();
	}
	boxColliders = getComponents<BoxCollider>();
	meshRenderers = getComponents<MeshRenderer>();
	auto& turnPoints = turnPointStore->getTurnPoints();
	std::erase_if(meshRenderers, [&](auto& meshRenderer) 
		{ 
			for (auto& turnPoint : turnPoints)
			{
				if (&*meshRenderer == &*turnPoint.getMeshRenderer())
				{
					return true;
				}
			}
			return false;
		});
}

bool Snake::canTurn(sf::Vector2f direction) const noexcept
{
	auto currentDirection{ transform->getForward() };
	return !WorldDirection::areOppositeDirections(currentDirection, direction);
}

void Snake::updateComponentsPositions(std::vector<sf::Vector2f> positions)
{
	for (size_t i{}; i < positions.size(); i++)
	{
		meshRenderers[i]->setPosition(positions[i]);
		boxColliders[i]->setPosition(positions[i]);
	}
}

void Snake::removeUsedUpTurnPoints(std::vector<sf::Vector2f> positions)
{
	if (turnPointStore->getTurnPoints().empty())
	{
		return;
	}

	auto& lastTurnPoint = turnPointStore->getTurnPoints()[turnPointStore->getTurnPoints().size() - 1];
	const auto& lastTurnPointPosition = lastTurnPoint.getPosition();
	const auto& lastPosition = positions[positions.size() - 1];

	if (Maths::dot(lastTurnPoint.getDirectionTo(), lastPosition - lastTurnPointPosition))
	{
		turnPointStore->remove(lastTurnPoint);
	}
}

bool Snake::isEatingFood(GameObject* gameObject) const
{
	return dynamic_cast<Consumable*>(gameObject) != nullptr;
}

bool Snake::isEatingItself() const
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