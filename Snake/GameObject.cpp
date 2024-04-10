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

vector<shared_ptr<Component>> GameObject::getComponents()
{
	return components;
}

void GameObject::addComponent(shared_ptr<Component> component)
{
	components.push_back(component);
}
