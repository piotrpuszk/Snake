#include "TurnPoint.h"

TurnPoint::TurnPoint(sf::Vector2f position, sf::Vector2f directionFrom, sf::Vector2f directionTo, MeshRenderer* meshRenderer)
	:
	position{ position },
	directionFrom{ directionFrom },
	directionTo{ directionTo },
	meshRenderer{ meshRenderer }
{
}

sf::Vector2f TurnPoint::getPosition() const noexcept
{
	return position;
}

sf::Vector2f TurnPoint::getDirectionFrom() const noexcept
{
	return directionFrom;
}

sf::Vector2f TurnPoint::getDirectionTo() const noexcept
{
	return directionTo;
}

MeshRenderer* TurnPoint::getMeshRenderer()
{
	return meshRenderer;
}

bool TurnPoint::operator==(const TurnPoint& rightSide)
{
	return getPosition() == rightSide.getPosition() && getDirectionFrom() == rightSide.getDirectionFrom() && getDirectionTo() == rightSide.getDirectionTo();
}

bool TurnPoint::operator!=(const TurnPoint& rightSide)
{
	return !(*this == rightSide);
}
