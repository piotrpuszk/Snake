#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "ObjectCollider.h"

class CollisionSystem
{
public:
	CollisionSystem();

	void checkCollisions();
	void deleteSnakeCollider(GameObject* gameObject);
	void deleteOtherCollider(GameObject* gameObject);
	void addSnakeCollider(ObjectCollider&& objectCollider);
	void addOtherCollider(ObjectCollider&& objectCollider);
private:
	void checkCollisions(auto begin1, auto end1, auto begin2, auto end2);
	void checkCollisions(auto begin, auto end);
	void checkCollision(ObjectCollider* collider1, ObjectCollider* collider2);

	std::vector<std::unique_ptr<ObjectCollider>> snakeColliders;
	std::vector<std::unique_ptr<ObjectCollider>> otherColliders;
};

