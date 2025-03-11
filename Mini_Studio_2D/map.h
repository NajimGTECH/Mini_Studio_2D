#pragma once
#include <vector>
#include <memory>
#include <fstream>
#include "mapElements.h"
#include "wall.h"


class Map
{
public:
	void createMap();
	void createWall(float x, float y, float width, float height);
	void displayMap(sf::RenderWindow& window);

	std::ifstream& getMapFile();
	std::vector<std::shared_ptr<MapElements>>& getMapElements();

private:

	std::ifstream m_mapFile;
	std::vector<std::shared_ptr<MapElements>> m_elements;

};

