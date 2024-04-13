#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"
#include "TurnPoint.h"
#include "SnakeMovement.h"
#include "MeshRenderer.h"
#include "TurnPointStore.h"
#include "SnakeComponentPositionIterator.h"
#include "BoxCollider.h"

class Snake : public GameObject, public Component
{
public:
	Snake(std::unique_ptr<TurnPointStore> turnPointStore, SnakeComponentPositionIterator snakeComponentPositionIterator);
	void awake() override;
	template<typename T>
	T* getComponent();
protected:
	void update() override;
	void fixedUpdate() override;
	void onEnterCollision(GameObject& gameObject) override;
private:
	std::unique_ptr<TurnPointStore> turnPointStore;
	SnakeComponentPositionIterator snakeComponentPositionIterator;
	SnakeMovement* snakeMovement;
	Transform* transform;
	std::vector<MeshRenderer*> meshRenderers;
	std::vector<BoxCollider*> boxColliders;

	void turn(sf::Vector2f direction);
	void move();
	void onEatFruit();
	void grow(int amount);
	bool canTurn(sf::Vector2f direction) const noexcept;
	void updateComponentsPositions();
	void removeUsedUpTurnPoints();
	bool IsEatingItself();
};

template<typename T>
inline T* Snake::getComponent()
{
	return GameObject::getComponent<T>();
}