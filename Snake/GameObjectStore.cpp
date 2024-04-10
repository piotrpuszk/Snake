#include "GameObjectStore.h"

GameObjectStore::GameObjectStore()
	:
	gameObjects{},
	meshRenderers{}
{
}

void GameObjectStore::addGameObject(shared_ptr<GameObject> gameObject)
{
	gameObjects.push_back(gameObject);
	auto meshRenderer = gameObject->getComponent<MeshRenderer>();
	if (meshRenderer)
	{
		meshRenderers.push_back(meshRenderer);
	}
}

void GameObjectStore::addGameObjects(vector<shared_ptr<GameObject>> gameObjects)
{
	for (auto go : gameObjects)
	{
		addGameObject(go);
	}
}

vector<shared_ptr<GameObject>> GameObjectStore::getGameObjects()
{
	return gameObjects;
}

vector<MeshRenderer*> GameObjectStore::getMeshRenderers()
{
	return meshRenderers;
}

void GameObjectStore::deleteGameObject(shared_ptr<GameObject> gameObject)
{
	std::erase(gameObjects, gameObject);
	std::erase_if(meshRenderers, [&](const auto meshRenderer) { return &*meshRenderer == &*gameObject.get()->getComponent<MeshRenderer>(); });
}
