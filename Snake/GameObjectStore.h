#pragma once
#include <vector>
#include <map>
#include <memory>

#include "GameObject.h"
#include "MeshRenderer.h"

using std::vector;

class GameObjectStore
{
public:
	GameObjectStore();
	void addGameObject(shared_ptr<GameObject> gameObject);
	void addGameObjects(vector<shared_ptr<GameObject>> gameObjects);
	vector<shared_ptr<GameObject>> getGameObjects();
	vector<MeshRenderer*> getMeshRenderers();
	void deleteGameObject(shared_ptr<GameObject> gameObject);
private:
	vector<shared_ptr<GameObject>> gameObjects;
	vector<MeshRenderer*> meshRenderers;
};

