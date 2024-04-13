#pragma once
#include <vector>
#include <memory>
#include "Component.h"

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
	template <typename T>
	std::vector<T*> getComponents();

	template <typename T, typename... Types>
	T* addComponent(Types... args);
	void addComponent(std::unique_ptr<Component> component);
private:
	int id;
	std::vector<std::unique_ptr<Component>> components;
	static int idSequence;
};

template<typename T>
inline T* GameObject::getComponent()
{
	for (const auto& component : components)
	{
		if (typeid(*component) == typeid(T))
		{
			return dynamic_cast<T*>(component.get());
		}
	}

	return nullptr;
}

template<typename T>
inline std::vector<T*> GameObject::getComponents()
{
	std::vector<T*> result{};
	for (const auto& component : components)
	{
		if (typeid(*component) == typeid(T))
		{
			result.emplace_back(dynamic_cast<T*>(component.get()));
		}
	}

	return result;
}

template <typename T, typename... Types>
inline T* GameObject::addComponent(Types... args)
{
	components.push_back(make_unique<T>(args...));
	return dynamic_cast<T*>(components.back().get());
}