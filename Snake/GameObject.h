#pragma once
#include <vector>
#include <memory>
#include <type_traits>
#include "Component.h"
#include "MeshRenderer.h"
#include <iostream>
#include <functional>

class GameObject
{
	friend class GameLoop;
	friend class CollisionSystem;
	friend class GameObjectStore;
public:
	GameObject();
	virtual ~GameObject() = default;
	int getId() const noexcept;

	template <typename T>
	T* getComponent();
	template <typename T>
	std::vector<T*> getComponents();

	template <typename T, typename... Types>
	T* addComponent(Types... args);
	template<typename T>
	T* addComponent(std::unique_ptr<T> component);
	template<typename T>
	void removeComponent(T* component);
private:
	virtual void awake() = 0;
	virtual void update() = 0;
	virtual void fixedUpdate() = 0;
	virtual void onEnterCollision(GameObject* gameObject) = 0;
	void setOnMeshRendererAdded(std::function<void(MeshRenderer*)> onMeshRendererAdded);
	void setOnMeshRendererRemoved(std::function<void(MeshRenderer*)> onMeshRendererRemoved);

	int id;
	std::vector<std::unique_ptr<Component>> components;
	static int idSequence;
	std::function<void(MeshRenderer*)> onMeshRendererAdded;
	std::function<void(MeshRenderer*)> onMeshRendererRemoved;
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
	components.push_back(std::make_unique<T>(args...));
	const auto& result{ dynamic_cast<T*>(components.back().get()) };
	if constexpr (std::is_same_v<T, MeshRenderer>)
	{
		if (onMeshRendererAdded)
		{
			onMeshRendererAdded(result);
		}
	}

	return result;
}

template<typename T>
inline T* GameObject::addComponent(std::unique_ptr<T> component)
{
	components.push_back(std::move(component));
	const auto& result{ dynamic_cast<T*>(components.back().get()) };
	if constexpr (std::is_same_v<T, MeshRenderer>)
	{
		if (onMeshRendererAdded)
		{
			onMeshRendererAdded(result);
		}
	}

	return result;
}

template<typename T>
inline void GameObject::removeComponent(T* component)
{
	erase_if(components, [&](const auto& e) { return &*e == &*component; });

	if constexpr (std::is_same_v<T, MeshRenderer>)
	{
		if (onMeshRendererRemoved)
		{
			onMeshRendererRemoved(component);
		}
	}
}
