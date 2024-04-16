#include "CollisionSystem.h"
#include <algorithm>
#include <iostream>

CollisionSystem::CollisionSystem()
	:
	otherColliders{},
	snakeColliders{}
{
}

void CollisionSystem::checkCollisions()
{
	checkCollisions(std::begin(snakeColliders), std::end(snakeColliders), std::begin(otherColliders), std::end(otherColliders));
}

void CollisionSystem::checkCollisions(auto begin1, auto end1, auto begin2, auto end2)
{
	for (; begin1 != end1; ++begin1)
	{
		for (; begin2 != end2; ++begin2)
		{
			checkCollision(begin1->get(), begin2->get());
		}
	}
}

void CollisionSystem::checkCollisions(auto begin, auto end)
{
	for (; begin != end; ++begin)
	{
		for (auto begin2 = begin + 1; begin2 != end; ++begin2)
		{
			checkCollision(begin->get(), begin2->get());
		}
	}
}

void CollisionSystem::checkCollision(ObjectCollider* collider1, ObjectCollider* collider2)
{
	if (collider1->getBoxCollider()->isColliding(*collider2->getBoxCollider()))
	{
		collider1->getGameObject()->onEnterCollision(collider2->getGameObject());
		collider2->getGameObject()->onEnterCollision(collider1->getGameObject());
	}
}

void CollisionSystem::deleteSnakeCollider(GameObject* gameObject)
{
	std::erase_if(snakeColliders, [&](auto& e) { return &*e->getGameObject() == &*gameObject; });
}

void CollisionSystem::deleteOtherCollider(GameObject* gameObject)
{
	std::erase_if(otherColliders, [&](auto& e) { return &*e->getGameObject() == &*gameObject; });
}

void CollisionSystem::addSnakeCollider(ObjectCollider&& objectCollider)
{
	snakeColliders.emplace_back(std::make_unique<ObjectCollider>(objectCollider));
}

void CollisionSystem::addOtherCollider(ObjectCollider&& objectCollider)
{
	otherColliders.emplace_back(std::make_unique<ObjectCollider>(objectCollider));
}
