#pragma once
#include "TurnPointTextureSelector.h"
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
#include "SnakeCollisionChecker.h"
#include "TurnDirectionHandler.h"
#include <tuple>
#include "TextureStore.h"

class Snake : public GameObject
{
public:
	Snake();
private:
	void awake() override;
	void update() override;
	void fixedUpdate() override;
	void onEnterCollision(GameObject* gameObject) override;

	void turn();
	void move();
	void onEatFruit(Consumable* consumable);
	void grow(int amount);
	void updateComponentsPositions(const std::vector<std::tuple<sf::Vector2f, float>>& positions);
	void removeUsedUpTurnPoints(const std::vector<std::tuple<sf::Vector2f, float>>& positions);
	bool isEatingItself(const std::vector<std::tuple<sf::Vector2f, float>>& positions) const;
	bool isEatingFood(GameObject* gameObject) const;

	SnakeMovement* snakeMovement;
	Transform* transform;
	std::vector<MeshRenderer*> meshRenderers;
	std::vector<BoxCollider*> boxColliders;
	SnakeCollisionChecker* snakeCollisionChecker;
	TurnPointStore* turnPointStore;
	GeneratorOfSnakePartPositions* generatorOfSnakePartPositions;
	TextureStore* textureStore;
	TurnPointTextureSelector* turnPointTextureSelector;
	
	float elementSize;
	float elementSizeSquared;
};