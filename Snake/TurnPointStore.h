#pragma once
#include <vector>
#include <algorithm>
#include <functional>
#include <functional>
#include "TurnPoint.h"
#include "Component.h"

class TurnPointStore : public Component
{
public:
	TurnPointStore(int turnPointRenderPriority);
	void setRemoveMeshRenderer(std::function<void(MeshRenderer*)> removeMeshRenderer);
	void add(TurnPoint& turnPoint);
	void add(TurnPoint&& turnPoint);
	void remove(TurnPoint& turnPoint);
	std::vector<TurnPoint>& getTurnPoints();
	const int getTurnPointRenderPriority() const noexcept;
private:
	std::vector<TurnPoint> turnPoints;
	std::function<void(MeshRenderer*)> removeMeshRenderer;
	int turnPointRenderPriority;
};

