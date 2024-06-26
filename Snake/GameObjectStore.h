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
	void deleteGameObject(GameObject* gameObject);
	std::vector<MeshRenderer*>& getMeshRenderers();
private:
	void onMeshRedererAdded(MeshRenderer* meshRenderer);
	void onMeshRedererRemoved(MeshRenderer* meshRenderer);

	std::vector<std::unique_ptr<GameObject>> gameObjects;
	std::vector<GameObject*> gameObjectRawPointers;
	std::vector<MeshRenderer*> meshRenderers;
};

