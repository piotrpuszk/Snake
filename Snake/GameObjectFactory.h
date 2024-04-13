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

class GameObjectFactory
{
public:
	GameObjectFactory(TextureStore textureStore, GameObjectStore& gameObjectStore);
	Snake* createSnake();
	Consumable* createFood01(sf::Vector2f position);

	template<typename T, typename... Types>
	T* create(Types... args);
private:
	TextureStore textureStore;
	GameObjectStore& gameObjectStore;
};

template<typename T, typename... Types>
inline T* GameObjectFactory::create(Types... args)
{
	if constexpr (std::is_same_v<T, Snake>)
	{
		return createSnake();
	}
}
