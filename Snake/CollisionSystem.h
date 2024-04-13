#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "ObjectCollider.h"

class CollisionSystem
{
public:
	CollisionSystem(std::vector<ObjectCollider>& objectColliders);

	void checkCollisions() const;
	void deleteCollider(GameObject* gameObject);
private:
	std::vector<ObjectCollider>& objectColliders;
};

