#pragma once
#include <vector>
#include <memory>
#include <fstream>

#include "mapElements.h"
#include "wall.h"
#include "door.h"
#include "button.h"
#include "npc.h"



class Map
{
public:
	Map();

	void createMap(int);
	void createWall(float x, float y, float width, float height);
	void createDoor(float x, float y, float width, float height);
	void createButton(float x, float y, float width, float height);
	void createNPC(float x, float y, float width, float height);
	void setDialogueBox(DialogueBox* db);
	void displayMap(sf::RenderWindow& window);

	std::vector<std::shared_ptr<MapElements>>& getAllWalls();
	std::vector<std::shared_ptr<MapElements>>& getAllDoors();
	std::vector<std::shared_ptr<MapElements>>& getAllButtons();
	std::vector<std::shared_ptr<MapElements>>& getAllNPCs();


	bool loaded = false;
	int lvl = 1;

private:

	std::ifstream m_mapFile;
	std::vector<std::shared_ptr<MapElements>> allWalls;
	std::vector<std::shared_ptr<MapElements>> allDoors;
	std::vector<std::shared_ptr<MapElements>> allButtons;
	std::vector<std::shared_ptr<MapElements>> allNPCs;
	DialogueBox* dialogueBox;


};

