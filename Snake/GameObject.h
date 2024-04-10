#pragma once
#include <vector>
#include <memory>
#include "Component.h"

using namespace std;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject() = default;

	virtual void awake() = 0;
	virtual void update() = 0;
	virtual void fixedUpdate() = 0;
	virtual void onEnterCollision(GameObject& gameObject) = 0;

	int getId() const noexcept;

	template <typename T>
	T* getComponent();
	shared_ptr<Component> getComponent();
	vector<shared_ptr<Component>> getComponents();

	template <typename T, typename... Types>
	T* addComponent(Types... args);
	void addComponent(shared_ptr<Component> component);
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
		if (typeid(*component) == typeid(T))
		{
			return dynamic_cast<T*>(component.get());
		}
	}

	return nullptr;
}

template <typename T, typename... Types>
inline T* GameObject::addComponent(Types... args)
{
	components.push_back(make_shared<T>(args...));
	return dynamic_cast<T*>(components.back().get());
}