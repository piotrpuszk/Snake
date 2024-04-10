#include "CollisionSystem.h"

CollisionSystem::CollisionSystem(vector<ObjectCollider>& objectColliders)
	:
	objectColliders{ objectColliders }
{
}

void CollisionSystem::checkCollisions()
{
	for (auto& objectCollider1 : objectColliders)
	{
		for (auto& objectCollider2 : objectColliders)
		{
			if (&objectCollider1 == &objectCollider2)
			{
				continue;
			}

			if (objectCollider1.getBoxCollider()->isColliding(*objectCollider2.getBoxCollider()))
			{
				objectCollider1.getGameObject()->onEnterCollision(*objectCollider2.getGameObject());
				objectCollider2.getGameObject()->onEnterCollision(*objectCollider1.getGameObject());
			}
		}
	}
}
