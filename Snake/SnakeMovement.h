#pragma once
#include "Component.h"
#include "Transform.h"
#include "GameObject.h"

class SnakeMovement : public GameObject, public Component
{
public:
	SnakeMovement(float speed);
	~SnakeMovement() = default;

	void awake() override;
	void update() override;
	void fixedUpdate() override;
	void onEnterCollision(GameObject& gameObject) override;

	void move();
	void turn(sf::Vector2f direction);
	float getSpeed() const noexcept;
	void setSpeed(float value) noexcept;
private:
	Transform* transform;
	float speed;
};

