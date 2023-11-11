#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "ObjectCollider.h"

using namespace std;

class CollisionSystem
{
public:
	CollisionSystem(vector<ObjectCollider>& objectColliders);

	void checkCollisions();
private:
	vector<ObjectCollider>& objectColliders;
};

