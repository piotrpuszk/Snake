#pragma once
#include "Component.h"
#include "Transform.h"
#include "GameObject.h"

class SnakeMovement : public Component
{
public:
	SnakeMovement(Transform* transform, float speed);
	~SnakeMovement() = default;

	void move();
	void turn(sf::Vector2f direction);
	float getSpeed() const noexcept;
	void setSpeed(float value) noexcept;
private:
	Transform* transform;
	float speed;
};

