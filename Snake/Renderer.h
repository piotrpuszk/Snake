#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "MeshRenderer.h"

using namespace std;

class Renderer
{
public:
	Renderer(vector<MeshRenderer>& meshRenderers);

	void render(sf::RenderWindow& window);
private:
	vector<MeshRenderer>& meshRenderers;
};

