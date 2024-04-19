#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>
#include "TurnPoint.h"
#include "Transform.h"
#include "Component.h"

class SnakeCollisionChecker : public Component
{
public:
	SnakeCollisionChecker(Transform* transform, float elementSize);
	bool IsCollidingWithItself(const std::vector<TurnPoint>& turnPoints, const std::vector<std::tuple<sf::Vector2f, float>>& positions);
private:
	float elementSize;
	float elementHalfOfSize;
	float elementSizeSquared;
	Transform* transform;
};

