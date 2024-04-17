#pragma once
#include "Component.h"
#include "Transform.h"
#include "GameObject.h"
#include "TurnPoint.h"
#include <vector>

class SnakeMovement : public Component
{
public:
	SnakeMovement(Transform* transform, float speed, float elementSize);
	~SnakeMovement() = default;

	void move();
	void turn(const sf::Vector2f& direction);
	float getSpeed() const noexcept;
	void setSpeed(float value) noexcept;
	bool canTurn(const sf::Vector2f& direction, const std::vector<TurnPoint>& turnPoints) const noexcept;
private:
	Transform* transform;
	float speed;
	float elementSize;
	float elementSizeSquared;
};

