#pragma once
#include <vector>
#include <memory>
#include <fstream>

#include "mapElements.h"
#include "wall.h"
#include "door.h"


class Map
{
public:
	void createMap();
	void createWall(float x, float y, float width, float height);
	void createDoor(float x, float y, float width, float height);
	void displayMap(sf::RenderWindow& window);

	std::vector<std::shared_ptr<MapElements>>& getAllWalls();
	std::vector<std::shared_ptr<MapElements>>& getAllDoors();

private:

	std::ifstream m_mapFile;
	std::vector<std::shared_ptr<MapElements>> allWalls;
	std::vector<std::shared_ptr<MapElements>> allDoors;

};

