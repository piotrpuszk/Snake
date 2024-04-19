#include "Snake.h"
#include "UserInputHandler.h"
#include "WorldDirection.h"
#include "GameObjectInstantiator.h"
#include "Maths.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include "Orientation.h"

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
	textureStore = getComponent<TextureStore>();

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
	const auto& positions{ generatorOfSnakePartPositions->getPositions(transform->getPosition(), transform->getForward()) };
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
		return;
	}

	if (dynamic_cast<Wall*>(gameObject) != nullptr)
	{
		std::cout << "Collision => Game over!\n";
		GameObjectInstantiator::destroy(this);
	}
}

void Snake::turn()
{
	if (!snakeMovement->canTurn(UserInputHandler::getLatestDirection(), turnPointStore->getTurnPoints()))
	{
		return;
	}

	sf::Sprite sprite{};
	sprite.setOrigin(meshRenderers[0]->getSprite().getOrigin());
	if (Orientation::isRight(transform->getForward()) && Orientation::isDown(UserInputHandler::getLatestDirection())
		|| Orientation::isUp(transform->getForward()) && Orientation::isLeft(UserInputHandler::getLatestDirection()))
	{
		sprite.setTexture(textureStore->getTurnPointLeftBottom());
	}
	else if (Orientation::isRight(transform->getForward()) && Orientation::isUp(UserInputHandler::getLatestDirection())
		|| Orientation::isDown(transform->getForward()) && Orientation::isLeft(UserInputHandler::getLatestDirection()))
	{
		sprite.setTexture(textureStore->getTurnPointLeftUp());
	}
	else if (Orientation::isLeft(transform->getForward()) && Orientation::isDown(UserInputHandler::getLatestDirection())
		|| Orientation::isUp(transform->getForward()) && Orientation::isRight(UserInputHandler::getLatestDirection()))
	{
		sprite.setTexture(textureStore->getTurnPointRightBottom());
	}
	else if (Orientation::isLeft(transform->getForward()) && Orientation::isUp(UserInputHandler::getLatestDirection())
		|| Orientation::isDown(transform->getForward()) && Orientation::isRight(UserInputHandler::getLatestDirection()))
	{
		sprite.setTexture(textureStore->getTurnPointRightUp());
	}
	auto meshRenderer{ addComponent<MeshRenderer>(sprite, 1) };
	meshRenderer->setPosition(transform->getPosition());
	turnPointStore->add(TurnPoint{ transform->getPosition(), transform->getForward(), UserInputHandler::getLatestDirection(), meshRenderer });

	snakeMovement->turn(UserInputHandler::getLatestDirection());

	const auto& latestTurnPoint{ turnPointStore->getTurnPoints()[0] };
	const auto angle{ Orientation::getAngle(latestTurnPoint.getDirectionFrom(), latestTurnPoint.getDirectionTo()) };
	meshRenderers[0]->rotate(angle);

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
	const auto index{ meshRenderers.size() - 1 };
	auto tail{ meshRenderers[index]->getSprite() };
	for (size_t i = 0; i < amount; i++)
	{
		if (i == amount - 1)
		{
			addComponent<MeshRenderer>(tail);
			meshRenderers[index]->setSprite(meshRenderers[1]->getSprite());
		}
		else
		{
			addComponent<MeshRenderer>(meshRenderers[1]->getSprite());
		}
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

void Snake::updateComponentsPositions(const std::vector<std::tuple<sf::Vector2f, float>>& positions)
{
	boxColliders[0]->setPosition(std::get<0>(positions[0]));

	const auto& headRotation{ meshRenderers[0]->getSprite().getRotation() };
	auto rotation{ headRotation };
	for (size_t i{}; i < positions.size(); i++)
	{
		meshRenderers[i]->setPosition(std::get<0>(positions[i]));

		rotation += std::get<1>(positions[i]);
		meshRenderers[i]->setRotation(rotation);
	}
}

void Snake::removeUsedUpTurnPoints(const std::vector<std::tuple<sf::Vector2f, float>>& positions)
{
	if (turnPointStore->getTurnPoints().empty())
	{
		return;
	}

	auto& lastTurnPoint = turnPointStore->getTurnPoints()[turnPointStore->getTurnPoints().size() - 1];
	const auto& lastTurnPointPosition = lastTurnPoint.getPosition();
	const auto& lastPosition = positions[positions.size() - 1];

	if (Maths::dot(lastTurnPoint.getDirectionTo(), std::get<0>(lastPosition) - lastTurnPointPosition))
	{
		turnPointStore->remove(lastTurnPoint);
	}
}

bool Snake::isEatingItself(const std::vector<std::tuple<sf::Vector2f, float>>& positions) const
{
	return snakeCollisionChecker->IsCollidingWithItself(turnPointStore->getTurnPoints(), positions);
}

bool Snake::isEatingFood(GameObject* gameObject) const
{
	return dynamic_cast<Consumable*>(gameObject) != nullptr;
}