#pragma once
#include "GameObject.h"

class Wall : public GameObject
{
private:
	void awake() override;
	void update() override;
	void fixedUpdate() override;
	void onEnterCollision(GameObject* gameObject) override;
};

