#pragma once
#include "GameObject.h"
#include "BoxCollider.h"

class ObjectCollider
{
public:
	ObjectCollider(GameObject& gameObject, BoxCollider& boxCollider);

	GameObject& getGameObject() noexcept;
	BoxCollider& getBoxCollider() noexcept;
private:
	GameObject& gameObject;
	BoxCollider& boxCollider;
};

