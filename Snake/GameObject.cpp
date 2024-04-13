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

void GameObject::addComponent(std::unique_ptr<Component> component)
{
	components.push_back(std::move(component));
}
