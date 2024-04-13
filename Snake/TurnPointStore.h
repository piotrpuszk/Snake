#pragma once
#include <vector>
#include <algorithm>
#include <functional>
#include <functional>
#include "TurnPoint.h"

class TurnPointStore
{
public:
	TurnPointStore();
	void setRemoveMeshRenderer(std::function<void(MeshRenderer*)> removeMeshRenderer);
	void add(TurnPoint& turnPoint);
	void add(TurnPoint&& turnPoint);
	void remove(TurnPoint& turnPoint);
	std::vector<TurnPoint>& getTurnPoints();
private:
	std::vector<TurnPoint> turnPoints;
	std::function<void(MeshRenderer*)> removeMeshRenderer;
};

