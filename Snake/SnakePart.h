#pragma once
#include "GameObject.h"
#include "SnakeMovement.h"
#include "MeshRenderer.h"
#include "BoxCollider.h"
#include <queue>
#include "TurnPoint.h"
#include "Orientation.h"
#include <functional>

using namespace std;

class SnakePart : public GameObject, public Component
{
public:
	SnakePart();
	~SnakePart() = default;

	void awake() override;
	void update() override;
	void fixedUpdate() override;
	void onEnterCollision(GameObject& gameObject) override;

	void move();
	void turn(sf::Vector2f direction);
	void tryToUseTurnPoint();
	void addTurnPoint(TurnPoint turnPoint);
	Transform& getTransform() const;
	void markAsHead();
	void markAsTail();
	bool isHead() const noexcept;
	bool isTail() const noexcept;
	void setOnTurnPointDeleted(std::function<void(TurnPoint)> onTurnPointDeleted);
private:
	SnakeMovement* snakeMovement;
	BoxCollider* boxCollider;
	Transform* transform;
	MeshRenderer* meshRenderer;
	queue<TurnPoint> turnPoints;
	bool isHeadInternal;
	bool isTailInternal;
	std::function<void(TurnPoint)> onTurnPointDeleted;
};

