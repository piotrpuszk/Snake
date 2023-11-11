#include "BoxCollider.h"

BoxCollider::BoxCollider(Transform& transform, sf::Vector2f size)
	:
	transform{ transform },
	size{ size }
{
}

bool BoxCollider::isColliding(BoxCollider other)
{
	auto otherPosition = other.getTransform().getPosition();
	auto otherHalfSize = other.getSize() * 0.5f;

	vector<sf::Vector2f> corners
	{
		sf::Vector2f{ otherPosition.x - otherHalfSize.x, otherPosition.y + otherHalfSize.y },
		sf::Vector2f{ otherPosition.x + otherHalfSize.x, otherPosition.y + otherHalfSize.y },
		sf::Vector2f{ otherPosition.x - otherHalfSize.x, otherPosition.y - otherHalfSize.y },
		sf::Vector2f{ otherPosition.x + otherHalfSize.x, otherPosition.y - otherHalfSize.y },
	};

	auto halfSize = size * 0.5f;

	sf::Vector2f xRange{ transform.getPosition().x - halfSize.x, transform.getPosition().x + halfSize.x };
	sf::Vector2f yRange{ transform.getPosition().y - halfSize.y, transform.getPosition().y + halfSize.y };

	for (const auto& corner : corners)
	{
		if (corner.x >= xRange.x && corner.x <= xRange.y && corner.y >= yRange.x && corner.y <= yRange.y)
		{
			return true;
		}
	}

	return false;
}

Transform& BoxCollider::getTransform() const noexcept
{
	return transform;
}

sf::Vector2f BoxCollider::getSize() const noexcept
{
	return size;
}
