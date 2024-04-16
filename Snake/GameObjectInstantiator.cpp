#include "GameObjectInstantiator.h"

GameObjectFactory* GameObjectInstantiator::gameObjectFactory = nullptr;
GameObjectStore* GameObjectInstantiator::gameObjectStore = nullptr;
CollisionSystem* GameObjectInstantiator::collisionSystem = nullptr;
std::queue<GameObject*> GameObjectInstantiator::gameObjectsToDelete = {};

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
	gameObjectsToDelete.push(gameObject);
}

void GameObjectInstantiator::destroy()
{
	while (!gameObjectsToDelete.empty())
	{
		if (std::is_same_v<Snake, decltype(gameObjectsToDelete.front())>)
		{
			collisionSystem->deleteSnakeCollider(gameObjectsToDelete.front());
		}
		else
		{
			collisionSystem->deleteOtherCollider(gameObjectsToDelete.front());
		}
		gameObjectStore->deleteGameObject(gameObjectsToDelete.front());
		gameObjectsToDelete.pop();
	}
}
