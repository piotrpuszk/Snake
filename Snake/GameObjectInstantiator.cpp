#include "GameObjectInstantiator.h"

GameObjectFactory* GameObjectInstantiator::gameObjectFactory = nullptr;
GameObjectStore* GameObjectInstantiator::gameObjectStore = nullptr;

void GameObjectInstantiator::setGameObjectFactory(GameObjectFactory* gameObjectFactory)
{
	GameObjectInstantiator::gameObjectFactory = gameObjectFactory;
}

void GameObjectInstantiator::setGameObjectStore(GameObjectStore* gameObjectStore)
{
	GameObjectInstantiator::gameObjectStore = gameObjectStore;
}
