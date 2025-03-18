#pragma once
#include <vector>
#include <unordered_map>
#include <memory>
#include <fstream>

#include "mapElements.h"
#include "wall.h"
#include "door.h"
#include "button.h"
#include "npc.h"
#include "terminal.h"
#include "stain.h"



class Map
{
public:
	Map();

	void createMap(int levelIndex);
	void createCustomLevel(std::string customLevelPath);

	void readMapFile();

	void createWall(float x, float y, float width, float height, int coordX, int coordY);
	void createDoor(float x, float y, float width, float height, int coordX, int coordY);
	void createButton(float x, float y, float width, float height, int coordX, int coordY);
	void createNPC(float x, float y, float width, float height, int coordX, int coordY);
	void createTerminal(float x, float y, float width, float height, int coordX, int coordY);
	void createLastDoor(float x, float y, float width, float height, int coordX, int coordY);
	void createStain(float x, float y, float width, float height, std::string text, int coordX, int coordY);


	void displayMap(sf::RenderWindow& window);

	std::vector<std::shared_ptr<MapElements>>& getAllWalls();
	std::vector<std::shared_ptr<MapElements>>& getAllDoors();
	std::vector<std::shared_ptr<MapElements>>& getAllButtons();
	std::vector<std::shared_ptr<MapElements>>& getAllNPCs();
	std::vector<std::shared_ptr<MapElements>>& getAllTerminals();
	std::vector<std::shared_ptr<MapElements>>& getAllStains();

	bool isSolid(int coordX, int coordY);

	bool loaded = false;
	int currentLevel = 0;

	std::string getCode();
	
private:

	std::string m_code;

	std::ifstream m_codeFile;
	std::ifstream m_mapFile;

	std::unordered_map<sf::Vector2i, std::shared_ptr<MapElements>, Vector2iHash> mapElementsCoordinates;

	std::vector<std::shared_ptr<MapElements>> allWalls;
	std::vector<std::shared_ptr<MapElements>> allDoors;
	std::vector<std::shared_ptr<MapElements>> allButtons;
	std::vector<std::shared_ptr<MapElements>> allNPCs;
	std::vector<std::shared_ptr<MapElements>> allTerminals;
	std::vector<std::shared_ptr<MapElements>> allStains;

	sf::Font m_font;
};

