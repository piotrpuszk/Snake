#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"
#include "TurnPoint.h"
#include "SnakeMovement.h"
#include "MeshRenderer.h"

class Snake : public GameObject, public Component
{
public:
	Snake();
	void awake() override;
	template<typename T>
	T* getComponent();
protected:
	void update() override;
	void fixedUpdate() override;
	void onEnterCollision(GameObject& gameObject) override;
private:
	vector<TurnPoint> turnPoints;
	SnakeMovement* snakeMovement;
	Transform* transform;
	vector<MeshRenderer*> meshRenderers;

	void turn(sf::Vector2f direction);
	void move();
	void onEatFruit();
	void grow(int amount);
	bool canTurn(sf::Vector2f direction) const noexcept;
	void updateMeshRendererPositions();
	void eraseTurnPoint(TurnPoint turnPoint);
};

template<typename T>
inline T* Snake::getComponent()
{
	return GameObject::getComponent<T>();
}