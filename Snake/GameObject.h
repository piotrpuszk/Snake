#pragma once
#include <vector>
#include <memory>
#include <type_traits>
#include "Component.h"
#include "MeshRenderer.h"

class GameObject
{
	friend class GameLoop;
	friend class CollisionSystem;
public:
	GameObject();
	virtual ~GameObject() = default;
	int getId() const noexcept;
	std::vector<MeshRenderer*>& getMeshRenderers() noexcept;

	template <typename T>
	T* getComponent();
	template <typename T>
	std::vector<T*> getComponents();

	template <typename T, typename... Types>
	T* addComponent(Types... args);
	template<typename T>
	void removeComponent(T* component);
private:
	virtual void awake() = 0;
	virtual void update() = 0;
	virtual void fixedUpdate() = 0;
	virtual void onEnterCollision(GameObject* gameObject) = 0;

	int id;
	std::vector<std::unique_ptr<Component>> components;
	std::vector<MeshRenderer*> meshRenderers;
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
	components.push_back(std::make_unique<T>(args...));
	auto result{ dynamic_cast<T*>(components.back().get()) };

	if (std::is_same_v<T, MeshRenderer>)
	{
		meshRenderers.push_back(dynamic_cast<MeshRenderer*>(result));
	}

	return result;
}

template<typename T>
inline void GameObject::removeComponent(T* component)
{
	if (std::is_same_v<T, MeshRenderer>)
	{
		erase_if(meshRenderers, [&](const auto& e) { return &*e == &*component; });
	}

	erase_if(components, [&](const auto& e) { return &*e == &*component; });
}
