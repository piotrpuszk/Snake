#include "GameObjectStore.h"
#include <iostream>

GameObjectStore::GameObjectStore()
	:
	gameObjects{},
	gameObjectRawPointers{}
{
}

GameObject* GameObjectStore::addGameObject(std::unique_ptr<GameObject> gameObject)
{
	gameObject->setOnMeshRendererAdded([this](MeshRenderer* e) {onMeshRedererAdded(e); });
	gameObject->setOnMeshRendererRemoved([this](MeshRenderer* e) {onMeshRedererRemoved(e); });
	gameObjects.push_back(std::move(gameObject));
	gameObjectRawPointers.push_back(gameObjects[gameObjects.size() - 1].get());
	
	for (auto& e : gameObjects[gameObjects.size() - 1].get()->getComponents<MeshRenderer>())
	{
		meshRenderers.push_back(e);
	}
	
	std::sort(std::begin(meshRenderers), std::end(meshRenderers), [&](const auto& left, const auto& right) { return *left < *right; });

	return gameObjectRawPointers[gameObjectRawPointers.size() - 1];
}

std::vector<GameObject*> GameObjectStore::addGameObjects(std::vector<std::unique_ptr<GameObject>> gameObjects)
{
	std::vector<GameObject*> result{};
	for (auto& go : gameObjects)
	{
		result.push_back(addGameObject(std::move(go)));
	}
	return result;
}

std::vector<GameObject*>& GameObjectStore::getGameObjects()
{
	return gameObjectRawPointers;
}

void GameObjectStore::deleteGameObject(GameObject* gameObject)
{
	for (const auto& toDelete : gameObject->getComponents<MeshRenderer>())
	{
		erase_if(meshRenderers, [&](const auto& e) { return &*e == &*toDelete; });
	}
	std::erase_if(gameObjectRawPointers, [&](const auto e) { return e->getId() == gameObject->getId(); });
	std::erase_if(gameObjects, [&](const auto& e) { return e->getId() == gameObject->getId(); });
}

std::vector<MeshRenderer*>& GameObjectStore::getMeshRenderers()
{
	return meshRenderers;
}

void GameObjectStore::onMeshRedererAdded(MeshRenderer* meshRenderer)
{
	meshRenderers.push_back(meshRenderer);
	std::sort(std::begin(meshRenderers), std::end(meshRenderers), [&](const auto& left, const auto& right) { return *left < *right; });
}

void GameObjectStore::onMeshRedererRemoved(MeshRenderer* meshRenderer)
{
	erase_if(meshRenderers, [&](const auto& e) { return &*e == &*meshRenderer; });
}
