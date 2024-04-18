#pragma once
#include <memory>
#include "GameObject.h"
#include "TextureStore.h"
#include "Snake.h"
#include "SnakeMovement.h"
#include "Transform.h"
#include <type_traits>
#include "GameObjectStore.h"
#include <memory>
#include "ConsumablesSpawner.h"
#include "BoxCollider.h"
#include "Wall.h"
#include "BackgroundTexture.h"

class GameObjectFactory
{
public:
	GameObjectFactory(TextureStore textureStore, GameObjectStore& gameObjectStore);
	
	template<typename T, typename... Types>
	T* create(Types&&... args);
private:
	Snake* createSnake();
	Consumable* createConsumable(sf::Vector2f position, size_t growSize = 1);
	ConsumablesSpawner* createConsumablesSpawner(GameSettings& gameSettings, sf::Time spawnInterval);
	Wall* createWall(sf::Vector2f position, sf::Vector2f size);
	BackgroundTexture* createBackgroundTexture(sf::Vector2f position, sf::Vector2f size);

	TextureStore textureStore;
	GameObjectStore& gameObjectStore;
};

template<typename T, typename... Types>
inline T* GameObjectFactory::create(Types&&... args)
{
	if constexpr (std::is_same_v<T, Snake>)
	{
		return createSnake();
	}

	if constexpr (std::is_same_v<T, Consumable>)
	{
		return createConsumable(std::forward<Types>(args)...);
	}

	if constexpr (std::is_same_v<T, ConsumablesSpawner>)
	{
		return createConsumablesSpawner(std::forward<Types>(args)...);
	}

	if constexpr (std::is_same_v<T, Wall>)
	{
		return createWall(std::forward<Types>(args)...);
	}

	if constexpr (std::is_same_v<T, BackgroundTexture>)
	{
		return createBackgroundTexture(std::forward<Types>(args)...);
	}
}