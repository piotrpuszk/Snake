#include "TurnPointStore.h"

TurnPointStore::TurnPointStore(int turnPointRenderPriority)
	:
	turnPoints{},
	turnPointRenderPriority{ turnPointRenderPriority }
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

const int TurnPointStore::getTurnPointRenderPriority() const noexcept
{
	return turnPointRenderPriority;
}
