#pragma once
#include "Component.h"

class TurnDirectionHandler : public Component
{
public:
	void update();
	sf::Vector2f& get();
	void reset();
private:
	sf::Vector2f latestRequestedTurnDirection;
};

