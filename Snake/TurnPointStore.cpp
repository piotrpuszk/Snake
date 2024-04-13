#include "TurnPointStore.h"

TurnPointStore::TurnPointStore()
	:
	turnPoints{},
	markedForRemoval{}
{
}

void TurnPointStore::add(TurnPoint& turnPoint)
{
	turnPoints.emplace(std::begin(turnPoints), turnPoint);
}

void TurnPointStore::add(TurnPoint&& turnPoint)
{
	turnPoints.emplace(std::begin(turnPoints), turnPoint);
}

void TurnPointStore::add(std::vector<TurnPoint>& turnPoints)
{
	for (auto& e : turnPoints)
	{
		add(e);
	}
}

void TurnPointStore::remove(TurnPoint& turnPoint)
{
	std::erase(turnPoints, turnPoint);
}

void TurnPointStore::remove(std::vector<TurnPoint>& turnPoints)
{
	for (auto& e : turnPoints)
	{
		remove(e);
	}
}

void TurnPointStore::remove(std::vector<TurnPoint>& turnPoints, int startIndex)
{
	std::for_each(std::begin(turnPoints) + startIndex, std::end(turnPoints), [&](auto& e) { remove(e); });
}

void TurnPointStore::markForRemoval(TurnPoint& turnPoint)
{
	markedForRemoval.push_back(turnPoint);
}

void TurnPointStore::markForRemoval(std::vector<TurnPoint>& turnPoints)
{
	for (auto& e : turnPoints)
	{
		markForRemoval(e);
	}
}

void TurnPointStore::markForRemoval(std::vector<TurnPoint>& turnPoints, std::vector<TurnPoint>::iterator begin)
{
	std::for_each(begin, std::end(turnPoints), [&](auto& e) { markForRemoval(e); });
}

void TurnPointStore::markForRemoval(std::vector<TurnPoint>& turnPoints, int startIndex)
{
	markForRemoval(turnPoints, std::begin(turnPoints) + startIndex);
}

void TurnPointStore::removeMarked()
{
	for (auto& e : markedForRemoval)
	{
		remove(e);
	}
}

std::vector<TurnPoint>& TurnPointStore::getTurnPoints() 
{
	return turnPoints;
}
