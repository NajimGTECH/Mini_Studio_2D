#pragma once
#include <vector>
#include <memory>
#include <fstream>
#include "mapElements.h"
#include "wall.h"
#include "door.h"
#include "button.h"
#include "terminal.h"
#include "stain.h"


class Map
{
public:
	Map();

	void createMap(int);

	void createWall(float x, float y, float width, float height);
	void createDoor(float x, float y, float width, float height);
	void createButton(float x, float y, float width, float height);
	void createTerminal(float x, float y, float width, float height);
	void createLastDoor(float x, float y, float width, float height);
	void createStain(float x, float y, float width, float height, std::string text);

	void displayMap(sf::RenderWindow& window);
	bool isWalkable(int x, int y) const;

	std::vector<std::shared_ptr<MapElements>>& getAllWalls();
	std::vector<std::shared_ptr<MapElements>>& getAllDoors();
	std::vector<std::shared_ptr<MapElements>>& getAllButtons();
	std::vector<std::shared_ptr<MapElements>>& getAllTerminals();
	std::vector<std::shared_ptr<MapElements>>& getAllStains();

	bool loaded = false;
	int lvl = 1;

	std::string getCode();
	
private:

	std::string m_code;
	std::ifstream m_codeFile;
	std::ifstream m_mapFile;
	std::vector<std::shared_ptr<MapElements>> allWalls;
	std::vector<std::shared_ptr<MapElements>> allDoors;
	std::vector<std::shared_ptr<MapElements>> allButtons;
	std::vector<std::shared_ptr<MapElements>> allTerminals;
	std::vector<std::shared_ptr<MapElements>> allStains;

};

