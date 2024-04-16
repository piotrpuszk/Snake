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
#include "SpawnerOfConsumables.h"

class GameObjectFactory
{
public:
	GameObjectFactory(TextureStore textureStore, GameObjectStore& gameObjectStore);
	
	template<typename T, typename... Types>
	T* create(Types... args);
private:
	TextureStore textureStore;
	GameObjectStore& gameObjectStore;

	Snake* create(Snake*);
	Consumable* create(Consumable*, sf::Vector2f position, size_t growSize = 1);
	SpawnerOfConsumables* create(SpawnerOfConsumables*, GameSettings& gameSettings, sf::Time spawnInterval);
};

template<typename T, typename... Types>
inline T* GameObjectFactory::create(Types... args)
{
	T* selector{};
	return create(selector, args...);
}
