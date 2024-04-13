#pragma once
#include "Transform.h"
#include "Component.h"
#include <vector>

using namespace std;

class BoxCollider : public Component {
public:
	BoxCollider(Transform* transform, sf::Vector2f size);
	~BoxCollider() = default;

	bool isColliding(BoxCollider other);
	Transform* getTransform() const noexcept;
	sf::Vector2f getSize() const noexcept;
private:
	Transform* transform;
	sf::Vector2f size;
};