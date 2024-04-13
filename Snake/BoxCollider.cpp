#include "BoxCollider.h"

BoxCollider::BoxCollider(Transform* transform, sf::Vector2f position, sf::Vector2f size)
	:
	transform{ transform },
	position{ position },
	size{ size }
{
}

bool BoxCollider::isColliding(BoxCollider other)
{
	auto otherPosition{ other.getPosition() };
	auto otherHalfSize{ other.getSize() * 0.5f };

	std::vector<sf::Vector2f> corners
	{
		sf::Vector2f{ otherPosition.x - otherHalfSize.x, otherPosition.y + otherHalfSize.y },
		sf::Vector2f{ otherPosition.x + otherHalfSize.x, otherPosition.y + otherHalfSize.y },
		sf::Vector2f{ otherPosition.x - otherHalfSize.x, otherPosition.y - otherHalfSize.y },
		sf::Vector2f{ otherPosition.x + otherHalfSize.x, otherPosition.y - otherHalfSize.y },
	};

	auto halfSize = size * 0.5f;

	sf::Vector2f xRange{ position.x - halfSize.x, position.x + halfSize.x };
	sf::Vector2f yRange{ position.y - halfSize.y, position.y + halfSize.y };

	for (const auto& corner : corners)
	{
		if (corner.x >= xRange.x && corner.x <= xRange.y && corner.y >= yRange.x && corner.y <= yRange.y)
		{
			return true;
		}
	}

	return false;
}

void BoxCollider::setPosition(sf::Vector2f value)
{
	position = value;
}

Transform* BoxCollider::getTransform() const noexcept
{
	return transform;
}

sf::Vector2f BoxCollider::getPosition() const noexcept
{
	return position;
}

sf::Vector2f BoxCollider::getSize() const noexcept
{
	return size;
}
