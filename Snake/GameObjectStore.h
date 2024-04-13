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
	void addGameObject(std::shared_ptr<GameObject> gameObject);
	void addGameObjects(std::vector<std::shared_ptr<GameObject>> gameObjects);
	std::vector<std::shared_ptr<GameObject>> getGameObjects();
	std::vector<MeshRenderer*> getMeshRenderers();
	void deleteGameObject(std::shared_ptr<GameObject> gameObject);
private:
	std::vector<std::shared_ptr<GameObject>> gameObjects;
	std::vector<MeshRenderer*> meshRenderers;
};

