#pragma once
#include "Transform.h"
#include <vector>
#include "Component.h"

using namespace std;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject() = default;

	virtual void update() = 0;
	virtual void fixedUpdate() = 0;
	virtual void onEnterCollision(GameObject& gameObject) = 0;

	int getId() const noexcept;

	template <typename T>
	T* getComponent();

	template <typename T>
	T* addComponent();
private:
	int id;
	vector<shared_ptr<Component>> components;
	static int idSequence;
};

template<typename T>
inline T* GameObject::getComponent()
{
	for (auto component : components)
	{
		if (typeid(component) == typeid(T))
		{
			return dynamic_cast<T*>(component.get());
		}
	}

	return nullptr;
}

template<typename T>
inline T* GameObject::addComponent()
{
	return nullptr;
	/*auto newComponent = make_shared<T>();
	components.push_back(newComponent);
	return newComponent.get();*/
}
