#pragma once
#include "Transform.h"
#include "Component.h"
#include <vector>

class BoxCollider : public Component {
public:
	BoxCollider(Transform* transform, sf::Vector2f position, sf::Vector2f size);
	~BoxCollider() = default;

	bool isColliding(BoxCollider other) const;
	sf::Vector2f getPosition() const noexcept;
	sf::Vector2f getSize() const noexcept;
	void setPosition(sf::Vector2f value);
private:
	Transform* transform;
	sf::Vector2f size;
	sf::Vector2f position;
};