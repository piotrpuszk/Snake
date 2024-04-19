#include "SnakeCollisionChecker.h"

SnakeCollisionChecker::SnakeCollisionChecker(Transform* transform, float elementSize)
	:
	transform{ transform },
	elementSize{ elementSize },
	elementHalfOfSize{ elementSize / 2.f },
	elementSizeSquared{ elementSize * elementSize }
{
}

bool SnakeCollisionChecker::IsCollidingWithItself(const std::vector<TurnPoint>& turnPoints, const std::vector<std::tuple<sf::Vector2f, float>>& positions)
{
	if (turnPoints.size() < 2)
	{
		return false;
	}

	const auto& head{ transform->getPosition() };

	std::vector<sf::Vector2f> headCorners
	{
		{ head.x - elementHalfOfSize, head.y - elementHalfOfSize },
		{ head.x + elementHalfOfSize, head.y - elementHalfOfSize },
		{ head.x - elementHalfOfSize, head.y + elementHalfOfSize },
		{ head.x + elementHalfOfSize, head.y + elementHalfOfSize }
	};

	float x1{};
	float y1{};
	float x2{};
	float y2{};

	for (size_t i{ 1 }; i < turnPoints.size(); i++)
	{
		auto position1{ turnPoints[i].getPosition() };
		auto position2{ i + 1 == turnPoints.size() ? std::get<0>(positions[positions.size() - 1]) : turnPoints[i + 1].getPosition()};

		if (position1.y == position2.y)
		{
			x1 = position1.x < position2.x ? position1.x : position2.x;
			y1 = position1.y;
			x2 = position1.x > position2.x ? position1.x : position2.x;
			y2 = position1.y;
		}
		else if (position1.x == position2.x)
		{
			y1 = position1.y < position2.y ? position1.y : position2.y;
			x1 = position1.x;
			y2 = position1.y > position2.y ? position1.y : position2.y;
			x2 = position1.x;
		}

		for (const auto& e : headCorners)
		{
			if (e.x >= x1 - elementHalfOfSize
				&& e.x <= x2 + elementHalfOfSize
				&& e.y >= y1 - elementHalfOfSize
				&& e.y <= y2 + elementHalfOfSize)
			{
				return true;
			}
		}

	}

	return false;
}
