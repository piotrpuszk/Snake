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
	elementSizeSquared{},
	textureStore{},
	turnPointTextureSelector{}
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
	turnPointTextureSelector = getComponent<TurnPointTextureSelector>();

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
		GameObjectInstantiator::instantiate<GameOver>();
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
		GameObjectInstantiator::instantiate<GameOver>();
		GameObjectInstantiator::destroy(this);
	}
}

void Snake::turn()
{
	if (!snakeMovement->canTurn(UserInputHandler::getLatestDirection(), turnPointStore->getTurnPoints()))
	{
		return;
	}

	auto [from, to] = std::pair{ transform->getForward(), UserInputHandler::getLatestDirection() };

	sf::Sprite sprite{};
	sprite.setOrigin(meshRenderers[0]->getSprite().getOrigin());
	sprite.setTexture(turnPointTextureSelector->select(from, to));

	auto meshRenderer{ addComponent<MeshRenderer>(sprite, turnPointStore->getTurnPointRenderPriority()) };
	meshRenderer->setPosition(transform->getPosition());

	turnPointStore->add(TurnPoint{ transform->getPosition(), from, to, meshRenderer });

	snakeMovement->turn(to);

	const auto angle{ Orientation::getAngle(from, to) };
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
	auto [position, rotationAngle] = positions[0];
	boxColliders[0]->setPosition(position);

	const auto& headRotation{ meshRenderers[0]->getSprite().getRotation() };
	auto rotation{ headRotation };
	for (size_t i{}; i < positions.size(); i++)
	{
		auto [position, rotationAngle] = positions[i];
		meshRenderers[i]->setPosition(position);

		rotation += rotationAngle;
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