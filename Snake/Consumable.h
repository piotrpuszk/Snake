#pragma once
#include "GameObject.h"

class Consumable : public GameObject
{
public:
	Consumable(size_t growSize);

	size_t getGrowSize() const noexcept;
private:
	void awake() override;
	void update() override;
	void fixedUpdate() override;
	void onEnterCollision(GameObject* gameObject) override;

	size_t growSize;
};

