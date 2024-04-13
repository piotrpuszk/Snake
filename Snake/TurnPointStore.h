#pragma once
#include <vector>
#include <algorithm>
#include <functional>
#include "TurnPoint.h"

class TurnPointStore
{
public:
	TurnPointStore();
	void add(TurnPoint& turnPoint);
	void add(TurnPoint&& turnPoint);
	void add(std::vector<TurnPoint>& turnPoints);
	void remove(TurnPoint& turnPoint);
	void remove(std::vector<TurnPoint>& turnPoints);
	void remove(std::vector<TurnPoint>& turnPoints, int startIndex);
	void markForRemoval(TurnPoint& turnPoint);
	void markForRemoval(std::vector<TurnPoint>& turnPoints);
	void markForRemoval(std::vector<TurnPoint>& turnPoints, std::vector<TurnPoint>::iterator begin);
	void markForRemoval(std::vector<TurnPoint>& turnPoints, int startIndex);
	void removeMarked();
	std::vector<TurnPoint>& getTurnPoints();
private:
	std::vector<TurnPoint> turnPoints;
	std::vector<TurnPoint> markedForRemoval;
};

