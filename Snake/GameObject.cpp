#include "GameObject.h"

int GameObject::idSequence = 0;

GameObject::GameObject()
	:
	id{++idSequence},
	components{}
{
}

int GameObject::getId() const noexcept
{
	return id;
}

std::vector<MeshRenderer*>& GameObject::getMeshRenderers() noexcept
{
	return meshRenderers;
}
