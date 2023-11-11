#include "ObjectCollider.h"

ObjectCollider::ObjectCollider(GameObject& gameObject, BoxCollider& boxCollider)
	:
	gameObject{ gameObject },
	boxCollider{ boxCollider }
{
}

GameObject& ObjectCollider::getGameObject() noexcept
{
	return gameObject;
}

BoxCollider& ObjectCollider::getBoxCollider() noexcept
{
	return boxCollider;
}
