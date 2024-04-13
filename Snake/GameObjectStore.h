#pragma once
#include <vector>
#include <map>
#include <memory>
#include "GameObject.h"
#include "MeshRenderer.h"

class GameObjectStore
{
public:
	GameObjectStore();
	GameObject* addGameObject(std::unique_ptr<GameObject> gameObject);
	std::vector<GameObject*> addGameObjects(std::vector<std::unique_ptr<GameObject>> gameObjects);
	std::vector<GameObject*>& getGameObjects();
	std::vector<MeshRenderer*>& getMeshRenderers();
	void deleteGameObject(GameObject* gameObject);
private:
	std::vector<std::unique_ptr<GameObject>> gameObjects;
	std::vector<MeshRenderer*> meshRenderers;
	std::vector<GameObject*> gameObjectRawPointers;
};

