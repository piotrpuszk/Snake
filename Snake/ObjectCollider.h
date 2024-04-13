#pragma once
#include "GameObject.h"
#include "BoxCollider.h"
#include <memory>

class ObjectCollider
{
public:
	ObjectCollider(GameObject* gameObject, BoxCollider* boxCollider);

	GameObject* getGameObject();
	BoxCollider* getBoxCollider() noexcept;
private:
	GameObject* gameObject;
	BoxCollider* boxCollider;
};

