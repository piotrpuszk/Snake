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
	if (isEatingItself(positions))
	{
		std::cout << "Game over!\n";
		GameObjectInstantiator::destroy(this);
	}
}

void Snake::onEnterCollision(GameObject* gameObject)
{


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
	if (!positions.empty())
	{
		boxColliders[0]->setPosition(positions[0]);
	}

	for (size_t i{}; i < positions.size(); i++)
	{
		meshRenderers[i]->setPosition(positions[i]);
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

bool Snake::isEatingItself(std::vector<sf::Vector2f> positions) const
{
	const auto& turnPoints{ turnPointStore->getTurnPoints() };

	if (turnPoints.size() < 2)
	{
		return false;
	}

	const auto& head{ transform->getPosition() };
	const auto& halfSize{ boxColliders[0]->getSize().x / 2.f };

	std::vector<sf::Vector2f> headCorners
	{ 
		{ head.x - halfSize, head.y - halfSize }, 
		{ head.x + halfSize, head.y - halfSize },
		{ head.x - halfSize, head.y + halfSize },
		{ head.x + halfSize, head.y + halfSize } 
	};

	float x1{};
	float y1{};
	float x2{};
	float y2{};

	for (size_t i{ 1 }; i < turnPoints.size(); i++)
	{
		auto position1{ turnPoints[i].getPosition() };
		auto position2{ i + 1 == turnPoints.size() ? positions[positions.size() - 1] : turnPoints[i + 1].getPosition() };

		if (position1.y == position2.y)
		{
			x1 = position1.x < position2.x ? position1.x : position2.x;
			y1 = position1.y;
			x2 = position1.x > position2.x ? position1.x : position2.x;
			y2 = position1.y;
		}
		else if (position1.x == position2.x)
		{
			y1 = position1.y < position2.y ? position1.y : position2.y;
			x1 = position1.x;
			y2 = position1.y > position2.y ? position1.y : position2.y;
			x2 = position1.x;
		}

		for (const auto& e : headCorners)
		{
			if (e.x >= x1 - halfSize
				&& e.x <= x2 + halfSize
				&& e.y >= y1 - halfSize
				&& e.y <= y2 + halfSize)
			{
				return true;
			}
		}

	}

	return false;
}

bool Snake::isEatingFood(GameObject* gameObject) const
{
	return dynamic_cast<Consumable*>(gameObject) != nullptr;
}