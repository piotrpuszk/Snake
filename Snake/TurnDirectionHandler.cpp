#include "TurnDirectionHandler.h"
#include "UserInputHandler.h"
#include "WorldDirection.h"

void TurnDirectionHandler::update()
{
	
}

sf::Vector2f& TurnDirectionHandler::get()
{
	return latestRequestedTurnDirection;
}

void TurnDirectionHandler::reset()
{
	latestRequestedTurnDirection = {};
}
