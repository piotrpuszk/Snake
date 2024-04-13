#include "GameObjectInstantiator.h"

GameObjectFactory* GameObjectInstantiator::gameObjectFactory = nullptr;
GameObjectStore* GameObjectInstantiator::gameObjectStore = nullptr;
CollisionSystem* GameObjectInstantiator::collisionSystem = nullptr;
std::vector<GameObject*> GameObjectInstantiator::gameObjectsToDelete = {};

void GameObjectInstantiator::setGameObjectFactory(GameObjectFactory* gameObjectFactory)
{
	GameObjectInstantiator::gameObjectFactory = gameObjectFactory;
}

void GameObjectInstantiator::setGameObjectStore(GameObjectStore* gameObjectStore)
{
	GameObjectInstantiator::gameObjectStore = gameObjectStore;
}

void GameObjectInstantiator::setCollisionSystem(CollisionSystem* collisionSystem)
{
	GameObjectInstantiator::collisionSystem = collisionSystem;
}

void GameObjectInstantiator::destroy(GameObject* gameObject)
{
	gameObjectsToDelete.push_back(gameObject);
}

void GameObjectInstantiator::destroy()
{
	for (auto& e : gameObjectsToDelete)
	{
		collisionSystem->deleteCollider(e);
		gameObjectStore->deleteGameObject(e);
	}
}
