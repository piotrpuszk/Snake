#pragma once
#include <vector>
#include "GameObject.h"
#include "SnakePart.h"

class Snake : GameObject, Component
{
public:
protected:
	void update() override;
	void fixedUpdate() override;
	void onEnterCollision(GameObject& gameObject) override;
private:
	std::vector<SnakePart> parts;

	void turn(sf::Vector2f direction);
	void move();
	void onEatFruit();
	void grow(int amount);
};

