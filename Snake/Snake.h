#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"
#include "TurnPoint.h"
#include "SnakeMovement.h"
#include "MeshRenderer.h"
#include "TurnPointStore.h"

class Snake : public GameObject, public Component
{
public:
	Snake(TurnPointStore turnPointStore, float partSize);
	void awake() override;
	template<typename T>
	T* getComponent();
protected:
	void update() override;
	void fixedUpdate() override;
	void onEnterCollision(GameObject& gameObject) override;
private:
	TurnPointStore turnPointStore;
	float partSize;
	SnakeMovement* snakeMovement;
	Transform* transform;
	vector<MeshRenderer*> meshRenderers;

	void turn(sf::Vector2f direction);
	void move();
	void onEatFruit();
	void grow(int amount);
	bool canTurn(sf::Vector2f direction) const noexcept;
	void updateMeshRendererPositions();

	void fillInDistanceToTurnPoint(size_t& turnPointIndex, size_t& tileIndex, sf::Vector2f& forward, sf::Vector2f& position);
	void fillInRemainingDistanceToTurnPoint(size_t& turnPointIndex, size_t& tileIndex, sf::Vector2f& position, sf::Vector2f& forward);
	void fillInDistanceAfterTurnPoints(sf::Vector2f& position, sf::Vector2f& forward, size_t& tileIndex);
};

template<typename T>
inline T* Snake::getComponent()
{
	return GameObject::getComponent<T>();
}