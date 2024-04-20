#pragma once
#include "TurnPointTextureSelector.h"
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
#include "GameOver.h"

class GameObjectFactory
{
public:
	GameObjectFactory(TextureStore textureStore, GameObjectStore& gameObjectStore, const GameSettings& settings);
	
	template<typename T, typename... Types>
	T* create(Types&&... args);
private:
	Snake* createSnake();
	Consumable* createConsumable(sf::Vector2f position, size_t growSize = 1);
	ConsumablesSpawner* createConsumablesSpawner(const sf::Vector2f& position, const sf::Vector2f& size, sf::Time spawnInterval);
	Wall* createWall(sf::Vector2f meshRendererPosition, 
		sf::Vector2f meshRendererGrowDirection, 
		float meshRenderersCount,
		float meshRendererSize,
		sf::Vector2f boxColliderPosition,
		sf::Vector2f boxColliderSize);
	BackgroundTexture* createBackgroundTexture();
	GameOver* createGameOver();

	TextureStore textureStore;
	GameObjectStore& gameObjectStore;
	const GameSettings& settings;
};

template<typename T, typename... Types>
inline T* GameObjectFactory::create(Types&&... args)
{
	if constexpr (std::is_same_v<T, Snake>)
	{
		return createSnake(std::forward<Types>(args)...);
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

	if constexpr (std::is_same_v<T, GameOver>)
	{
		return createGameOver(std::forward<Types>(args)...);
	}
}