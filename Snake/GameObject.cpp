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

void GameObject::setOnMeshRendererAdded(std::function<void(MeshRenderer*)> onMeshRendererAdded)
{
	this->onMeshRendererAdded = onMeshRendererAdded;
}

void GameObject::setOnMeshRendererRemoved(std::function<void(MeshRenderer*)> onMeshRendererRemoved)
{
	this->onMeshRendererRemoved = onMeshRendererRemoved;
}
