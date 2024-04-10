#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"
#include "SnakePart.h"

class Snake : public GameObject, public Component
{
public:
	Snake() = default;
	Snake(vector<shared_ptr<SnakePart>> parts);
	void awake() override;
	template<typename T>
	T* getComponent();
	template<typename T>
	std::vector<T*> getComponentsInChildren();
protected:
	void update() override;
	void fixedUpdate() override;
	void onEnterCollision(GameObject& gameObject) override;
private:
	vector<shared_ptr<SnakePart>> parts;
	vector<shared_ptr<SnakePart>> turnPointWorkarounds;

	void turn(sf::Vector2f direction);
	void move();
	void onEatFruit();
	void grow(int amount);
	bool canTurn(sf::Vector2f direction) const noexcept;
};

template<typename T>
inline T* Snake::getComponent()
{
	return GameObject::getComponent<T>();
}

template<typename T>
inline std::vector<T*> Snake::getComponentsInChildren()
{
	std::vector<T*> result{};

	for (auto& part : parts)
	{
		result.push_back(part.getComponent<T>());
	}

	return result;
}
