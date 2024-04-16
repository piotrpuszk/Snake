#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"
#include "TurnPoint.h"
#include "SnakeMovement.h"
#include "MeshRenderer.h"
#include "TurnPointStore.h"
#include "GeneratorOfSnakePartPositions.h"
#include "BoxCollider.h"
#include "Consumable.h"

class Snake : public GameObject
{
public:
	Snake(std::unique_ptr<TurnPointStore> turnPointStore, GeneratorOfSnakePartPositions generatorOfSnakePartPositions);
private:
	void awake() override;
	void update() override;
	void fixedUpdate() override;
	void onEnterCollision(GameObject* gameObject) override;

	std::unique_ptr<TurnPointStore> turnPointStore;
	GeneratorOfSnakePartPositions generatorOfSnakePartPositions;
	SnakeMovement* snakeMovement;
	Transform* transform;
	std::vector<MeshRenderer*> meshRenderers;
	std::vector<BoxCollider*> boxColliders;

	void turn(sf::Vector2f direction);
	void move();
	void onEatFruit(Consumable* consumable);
	void grow(int amount);
	bool canTurn(sf::Vector2f direction) const noexcept;
	void updateComponentsPositions(std::vector<sf::Vector2f> positions);
	void removeUsedUpTurnPoints(std::vector<sf::Vector2f> positions);
	bool isEatingItself(std::vector<sf::Vector2f> positions) const;
	bool isEatingFood(GameObject* gameObject) const;
};