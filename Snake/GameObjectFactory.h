#pragma once
#include <memory>
#include "GameObject.h"
#include "TextureStore.h"
#include "Snake.h"
#include "SnakePart.h"
#include "SnakeMovement.h"
#include "Transform.h"
#include <type_traits>
#include "GameObjectStore.h"
#include <memory>

class GameObjectFactory
{
public:
	GameObjectFactory(TextureStore textureStore, GameObjectStore& gameObjectStore);
	std::shared_ptr<Snake> createSnake();
	std::shared_ptr<SnakePart> createSnakePart(sf::Vector2f snakePartSize);

	template<typename T, typename... Types>
	shared_ptr<T> create(Types... args);
private:
	TextureStore textureStore;
	GameObjectStore& gameObjectStore;
};

template<typename T, typename... Types>
inline shared_ptr<T> GameObjectFactory::create(Types... args)
{
	if constexpr (std::is_same_v<T, Snake>)
	{
		return createSnake();
	}

	if constexpr (std::is_same_v<T, SnakePart>)
	{
		return createSnakePart(args...);
	}
}
