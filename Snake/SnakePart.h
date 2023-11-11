#pragma once
#include "GameObject.h"
#include "SnakeMovement.h"
#include "MeshRenderer.h"
#include "BoxCollider.h"
#include <queue>
#include "TurnPoint.h"

using namespace std;

class SnakePart : public GameObject, public Component
{
public:
	SnakePart();
	~SnakePart() = default;

	void update() override;
	void fixedUpdate() override;
	void onEnterCollision(GameObject& gameObject) override;

	void move();
	void turn(sf::Vector2f direction);
	void tryToUseTurnPoint();
	void addTurnPoint(TurnPoint turnPoint);
private:
	SnakeMovement* snakeMovement;
	BoxCollider* boxCollider;
	Transform* transform;
	queue<TurnPoint> turnPoints;
};

