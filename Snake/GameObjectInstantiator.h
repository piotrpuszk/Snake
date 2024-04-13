#pragma once
#include <vector>
#include "GameObjectStore.h"
#include "GameObjectFactory.h"
#include "CollisionSystem.h"

class GameObjectInstantiator
{
	friend class GameLoop;
public:
	static void setGameObjectFactory(GameObjectFactory* gameObjectFactory);
	static void setGameObjectStore(GameObjectStore* gameObjectStore);
	static void setCollisionSystem(CollisionSystem* collisionSystem);
	template <typename T, typename... Types>
	static T* instantiate(Types... args);
	static void destroy(GameObject* gameObject);
private:
	static void destroy();

	static GameObjectFactory* gameObjectFactory;
	static GameObjectStore* gameObjectStore;
	static CollisionSystem* collisionSystem;
	static std::vector<GameObject*> gameObjectsToDelete;
};

template<typename T, typename... Types>
inline T* GameObjectInstantiator::instantiate(Types... args)
{
	return gameObjectFactory->create<T>(args...);
}