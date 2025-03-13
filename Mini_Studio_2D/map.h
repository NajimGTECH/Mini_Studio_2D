#pragma once
#include <vector>
#include <memory>
#include <fstream>
#include "mapElements.h"
#include "wall.h"
#include "door.h"
#include "button.h"


class Map
{
public:
	Map();

	void createMap(int);
	void createWall(float x, float y, float width, float height);
	void createDoor(float x, float y, float width, float height);
	void createButton(float x, float y, float width, float height);
	void displayMap(sf::RenderWindow& window);
	bool isWalkable(int x, int y) const;

	std::vector<std::shared_ptr<MapElements>>& getAllWalls();
	std::vector<std::shared_ptr<MapElements>>& getAllDoors();
	std::vector<std::shared_ptr<MapElements>>& getAllButtons();

	bool loaded = false;
	int lvl = 1;

private:

	std::ifstream m_mapFile;
	std::vector<std::shared_ptr<MapElements>> allWalls;
	std::vector<std::shared_ptr<MapElements>> allDoors;
	std::vector<std::shared_ptr<MapElements>> allButtons;

};

