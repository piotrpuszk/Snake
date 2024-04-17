#include "Snake.h"
#include "UserInputHandler.h"
#include "WorldDirection.h"
#include "GameObjectInstantiator.h"
#include "Maths.h"
#include <cmath>
#include <algorithm>
#include <iostream>

Snake::Snake()
	:
	turnPointStore{},
	generatorOfSnakePartPositions{},
	snakeMovement{},
	transform{},
	meshRenderers{},
	boxColliders{},
	snakeCollisionChecker{},
	elementSize{},
	elementSizeSquared{}
{
	
}

void Snake::awake()
{
	meshRenderers = getComponents<MeshRenderer>();
	boxColliders = getComponents<BoxCollider>();
	snakeMovement = getComponent<SnakeMovement>();
	transform = getComponent<Transform>();
	snakeCollisionChecker = getComponent<SnakeCollisionChecker>();
	turnPointStore = getComponent<TurnPointStore>();
	generatorOfSnakePartPositions = getComponent<GeneratorOfSnakePartPositions>();

	elementSize = boxColliders[0]->getSize().x;
	elementSizeSquared = elementSize * elementSize;
	turnPointStore->setRemoveMeshRenderer(
		[this](auto e) 
		{
			removeComponent(e);
		}
	);
}

void Snake::update()
{
}

void Snake::fixedUpdate()
{
	turn();
	move();
	const auto& positions = generatorOfSnakePartPositions->getPositions(transform->getPosition(), transform->getForward());
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

void Snake::turn()
{
	if (!snakeMovement->canTurn(UserInputHandler::getLatestDirection(), turnPointStore->getTurnPoints()))
	{
		return;
	}

	auto meshRenderer{ addComponent<MeshRenderer>(meshRenderers[0]->getSprite()) };
	meshRenderer->setPosition(transform->getPosition());
	turnPointStore->add(TurnPoint{ transform->getPosition(), transform->getForward(), UserInputHandler::getLatestDirection(), meshRenderer});
	
	snakeMovement->turn(UserInputHandler::getLatestDirection());
	
	UserInputHandler::resetLatestDirection();
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
		generatorOfSnakePartPositions->increasePositionCount();
	}
	meshRenderers = getComponents<MeshRenderer>();
	std::erase_if(meshRenderers, [&](auto& meshRenderer)
		{
			for (auto& turnPoint : turnPointStore->getTurnPoints())
			{
				if (&*meshRenderer == &*turnPoint.getMeshRenderer())
				{
					return true;
				}
			}
			return false;
		});
}

void Snake::updateComponentsPositions(const std::vector<sf::Vector2f>& positions)
{
	boxColliders[0]->setPosition(positions[0]);

	for (size_t i{}; i < positions.size(); i++)
	{
		meshRenderers[i]->setPosition(positions[i]);
	}
}

void Snake::removeUsedUpTurnPoints(const std::vector<sf::Vector2f>& positions)
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

bool Snake::isEatingItself(const std::vector<sf::Vector2f>& positions) const
{
	return snakeCollisionChecker->IsCollidingWithItself(turnPointStore->getTurnPoints(), positions);
}

bool Snake::isEatingFood(GameObject* gameObject) const
{
	return dynamic_cast<Consumable*>(gameObject) != nullptr;
}