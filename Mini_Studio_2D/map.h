#pragma once
#include <vector>
#include "mapElements.h"
#include "wall.h"
#include <fstream>



class Map
{
private:

	std::ifstream mapFile;

	std::vector <MapElements*> walls;

public:

	void createMap();

	void createWall(float x, float y, float width, float height);

	void displayMap(sf::RenderWindow& window);

};

