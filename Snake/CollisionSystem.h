#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "ObjectCollider.h"

class CollisionSystem
{
public:
	CollisionSystem(std::vector<ObjectCollider>& objectColliders);

	void checkCollisions();
private:
	std::vector<ObjectCollider>& objectColliders;
};

