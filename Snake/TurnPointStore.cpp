#include "TurnPointStore.h"

TurnPointStore::TurnPointStore()
	:
	turnPoints{}
{
}

void TurnPointStore::setRemoveMeshRenderer(std::function<void(MeshRenderer*)> removeMeshRenderer)
{
	this->removeMeshRenderer = removeMeshRenderer;
}

void TurnPointStore::add(TurnPoint& turnPoint)
{
	turnPoints.emplace(std::begin(turnPoints), turnPoint);
}

void TurnPointStore::add(TurnPoint&& turnPoint)
{
	turnPoints.emplace(std::begin(turnPoints), turnPoint);
}

void TurnPointStore::remove(TurnPoint& turnPoint)
{
	removeMeshRenderer(turnPoint.getMeshRenderer());
	std::erase(turnPoints, turnPoint);
}

std::vector<TurnPoint>& TurnPointStore::getTurnPoints()
{
	return turnPoints;
}
