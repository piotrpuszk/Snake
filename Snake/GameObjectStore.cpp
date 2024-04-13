#include "GameObjectStore.h"

GameObjectStore::GameObjectStore()
	:
	gameObjects{},
	gameObjectRawPointers{}
{
}

GameObject* GameObjectStore::addGameObject(std::unique_ptr<GameObject> gameObject)
{
	gameObjects.push_back(std::move(gameObject));
	gameObjectRawPointers.push_back(gameObjects[gameObjects.size() - 1].get());
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
	std::erase_if(gameObjectRawPointers, [&](const auto e) { return &*e == &*gameObject; });
	std::erase_if(gameObjects, [&](const auto& e) { return &*e == &*gameObject; });
}
