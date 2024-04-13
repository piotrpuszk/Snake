#include "BoxCollider.h"
#include <iostream>

BoxCollider::BoxCollider(Transform* transform, sf::Vector2f position, sf::Vector2f size)
	:
	transform{ transform },
	position{ position },
	size{ size }
{
}

bool BoxCollider::isColliding(BoxCollider other) const
{
	auto otherHalfSize{ other.size * 0.5f };

	std::vector<sf::Vector2f> corners
	{
		sf::Vector2f{ other.position.x - otherHalfSize.x, other.position.y + otherHalfSize.y },
		sf::Vector2f{ other.position.x + otherHalfSize.x, other.position.y + otherHalfSize.y },
		sf::Vector2f{ other.position.x - otherHalfSize.x, other.position.y - otherHalfSize.y },
		sf::Vector2f{ other.position.x + otherHalfSize.x, other.position.y - otherHalfSize.y },
	};

	auto halfSize = size * 0.5f;

	sf::Vector2f xRange{ position.x - halfSize.x, position.x + halfSize.x };
	sf::Vector2f yRange{ position.y - halfSize.y, position.y + halfSize.y };

	for (const auto& corner : corners)
	{
		if (corner.x > xRange.x && corner.x < xRange.y && corner.y > yRange.x && corner.y < yRange.y)
		{
			return true;
		}
		if ((corner.x == xRange.x || corner.x == xRange.y) && (corner.y == yRange.x || corner.y == yRange.y))
		{
			return transform->getForward() != other.transform->getForward();
		}
	}

	return false;
}

sf::Vector2f BoxCollider::getPosition() const noexcept
{
	return position;
}

sf::Vector2f BoxCollider::getSize() const noexcept
{
	return size;
}

void BoxCollider::setPosition(sf::Vector2f value)
{
	position = value;
}
