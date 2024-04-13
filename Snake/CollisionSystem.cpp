#include "CollisionSystem.h"
#include <algorithm>

CollisionSystem::CollisionSystem(std::vector<ObjectCollider>& objectColliders)
	:
	objectColliders{ objectColliders }
{
}

void CollisionSystem::checkCollisions() const
{
	for (auto objectCollider1 = std::begin(objectColliders); objectCollider1 != std::end(objectColliders); ++objectCollider1)
	{
		for (auto objectCollider2 = objectCollider1 + 1; objectCollider2 != std::end(objectColliders); ++objectCollider2)
		{
			if (objectCollider1->getBoxCollider()->isColliding(*objectCollider2->getBoxCollider()))
			{
				objectCollider1->getGameObject()->onEnterCollision(objectCollider2->getGameObject());
				objectCollider2->getGameObject()->onEnterCollision(objectCollider1->getGameObject());
			}
		}
	}
}

void CollisionSystem::deleteCollider(GameObject* gameObject)
{
	std::erase_if(objectColliders, [&](auto& e) { return &*e.getGameObject() == &*gameObject; });
}
