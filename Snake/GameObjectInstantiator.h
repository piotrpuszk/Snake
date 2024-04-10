#pragma once
#include <vector>
#include "GameObjectStore.h"
#include "GameObjectFactory.h"

class GameObjectInstantiator
{
public:
	static void setGameObjectFactory(GameObjectFactory* gameObjectFactory);
	static void setGameObjectStore(GameObjectStore* gameObjectStore);
	template <typename T, typename... Types>
	static shared_ptr<T> instantiate(Types... args);
	template <typename T>
	static void destroy(shared_ptr<T> gameObject);
private:
	static GameObjectFactory* gameObjectFactory;
	static GameObjectStore* gameObjectStore;
};

template<typename T, typename... Types>
inline shared_ptr<T> GameObjectInstantiator::instantiate(Types... args)
{
	return gameObjectFactory->create<T>(args...);
}

template<typename T>
inline void GameObjectInstantiator::destroy(shared_ptr<T> gameObject)
{
	gameObjectStore->deleteGameObject(gameObject);
}
