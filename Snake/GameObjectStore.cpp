#include "GameObjectStore.h"

GameObjectStore::GameObjectStore()
	:
	gameObjects{},
	meshRenderers{}
{
}

void GameObjectStore::addGameObject(std::shared_ptr<GameObject> gameObject)
{
	gameObjects.push_back(gameObject);
	for (auto meshRenderer: gameObject->getComponents<MeshRenderer>())
	{
		meshRenderers.push_back(meshRenderer);
	}
}

void GameObjectStore::addGameObjects(std::vector<std::shared_ptr<GameObject>> gameObjects)
{
	for (auto go : gameObjects)
	{
		addGameObject(go);
	}
}

std::vector<std::shared_ptr<GameObject>> GameObjectStore::getGameObjects()
{
	return gameObjects;
}

std::vector<MeshRenderer*> GameObjectStore::getMeshRenderers()
{
	return meshRenderers;
}

void GameObjectStore::deleteGameObject(std::shared_ptr<GameObject> gameObject)
{
	std::erase(gameObjects, gameObject);
	std::erase_if(meshRenderers, [&](const auto meshRenderer) { return &*meshRenderer == &*gameObject.get()->getComponent<MeshRenderer>(); });
}
