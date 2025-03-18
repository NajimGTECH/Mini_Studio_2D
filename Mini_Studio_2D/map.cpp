#include "map.h"

Map::Map() 
{
	if (!m_font.loadFromFile("Assets/TexteMenu/SolarPunk.otf")) {
		std::cerr << "Erreur : Impossible de charger la police SolarPunk.otf" << std::endl;
	}
}


void Map::createMap(int levelIndex) {

	currentLevel++;

	m_mapFile.close();
	m_codeFile.close();
	m_mapFile.open("Maps/Level_" + std::to_string(levelIndex) + ".txt");
	m_codeFile.open("codes.txt");

	//clearing everything from the previous map
	allWalls.clear();
	allButtons.clear();
	allDoors.clear();
	allTerminals.clear();
	allStains.clear();

	if (!m_mapFile) {
		std::cerr << "unable to open map file";
	}
	if (!m_codeFile) {
		std::cerr << "unable to open code file";
	}

	std::string line;
	int currentLine = 0;

	while (std::getline(m_codeFile, line)) {
		currentLine++;
		if (currentLine == levelIndex) {  // Si on atteint la ligne du niveau demandé
			m_code = line;
			std::cout << "got it" << std::endl;
			break;
		}
	}
	std::cout << m_code << " est le code" << std::endl;

	readMapFile();
}

void Map::createCustomLevel(std::string customLevelPath)
{
	m_mapFile.close();
	m_codeFile.close();
	m_mapFile.open("CustomLevels/" + customLevelPath);
	m_codeFile.open("codes.txt");

	//clearing everything from the previous map
	allWalls.clear();
	allButtons.clear();
	allDoors.clear();
	allTerminals.clear();
	allStains.clear();

	if (!m_mapFile) {
		std::cerr << "unable to open map file: " << "CustomLevels/" + customLevelPath << std::endl;
	}
	if (!m_codeFile) {
		std::cerr << "unable to open code file";
	}

	readMapFile();
}

void Map::readMapFile()
{
	int i = 0, x = 0, y = 0, j = 0;
	char ch;

	int coordX = 0;
	int coordY = 0;

	while (m_mapFile.get(ch)) {

		//std::cout << "Spawning map element at: [" << coordX << ", " << coordY << "]\n";

		switch (ch)
		{
		case '#': createWall(x, y, 60, 60, coordX, coordY); x += 60; i++; coordX++; break;
		case 'D': createDoor(x, y, 60, 60, coordX, coordY); x += 60; i++; coordX++; break;
		case 'B': createButton(x, y, 60, 60, coordX, coordY); x += 60; i++; coordX++; break;

		case 'N': createNPC(x, y, 60, 60, coordX, coordY); x += 60; i++; coordX++; break;

		case 'T': createTerminal(x, y, 60, 60, coordX, coordY); x += 60; i++; coordX++; break;
		case 'P': createLastDoor(x, y, 60, 60, coordX, coordY); x += 60; i++; coordX++; break;
		case ' ': mapElementsCoordinates[{coordX, coordY}] = nullptr; x += 60; i++; coordX++; break;

			//Stains:
		case '~': createStain(x, y, 60, 60, "", coordX, coordY); x += 60; i++; coordX++; break;
		case '0': createStain(x, y, 60, 60, "0", coordX, coordY); x += 60; i++; coordX++; break;
		case '1': createStain(x, y, 60, 60, "1", coordX, coordY); x += 60; i++; coordX++; break;
		case '2': createStain(x, y, 60, 60, "2", coordX, coordY); x += 60; i++; coordX++; break;
		case '3': createStain(x, y, 60, 60, "3", coordX, coordY); x += 60; i++; coordX++; break;
		case '4': createStain(x, y, 60, 60, "4", coordX, coordY); x += 60; i++; coordX++; break;
		case '5': createStain(x, y, 60, 60, "5", coordX, coordY); x += 60; i++; coordX++; break;
		case '6': createStain(x, y, 60, 60, "6", coordX, coordY); x += 60; i++; coordX++; break;
		case '7': createStain(x, y, 60, 60, "7", coordX, coordY); x += 60; i++; coordX++; break;
		case '8': createStain(x, y, 60, 60, "8", coordX, coordY); x += 60; i++; coordX++; break;
		case '9': createStain(x, y, 60, 60, "9", coordX, coordY); x += 60; i++; coordX++; break;

		}

		if (i == 32) {
			y += 60; x = 0; i = 0; j++;
		}

		if (j == 18) {
			y = 0; x = 0; i = 0; j++;
		}

		if (coordX == 32)
		{
			coordX = 0;
			coordY++;
		}
	}
}

void Map::createTerminal(float x, float y, float width, float height, int coordX, int coordY) {
	auto newTerm = std::make_shared<Terminal>(x, y, width, height, 2);
	allTerminals.push_back(newTerm);
	mapElementsCoordinates[{coordX, coordY}] = newTerm;
}
 
void Map::createStain(float x, float y, float width, float height, std::string text, int coordX, int coordY)
{
	auto newStain = std::make_shared<Stain>(x, y, width, height, text);
	allStains.push_back(newStain);
	mapElementsCoordinates[{coordX, coordY}] = newStain;
}

void Map::createWall(float x, float y, float width, float height, int coordX, int coordY) {
	auto newWall = std::make_shared<Wall>(x, y, width, height, 0);
	allWalls.push_back(newWall);
	mapElementsCoordinates[{coordX, coordY}] = newWall;
}

void Map::createDoor(float x, float y, float width, float height, int coordX, int coordY) {
	auto newDoor = std::make_shared<Door>(x, y, width, height, 1);
	allDoors.push_back(newDoor);
	mapElementsCoordinates[{coordX, coordY}] = newDoor;
}

void Map::createButton(float x, float y, float width, float height, int coordX, int coordY) {
	auto newButton = std::make_shared<Button>(x, y, width, height, 1);
	allButtons.push_back(newButton);
	mapElementsCoordinates[{coordX, coordY}] = newButton;
}

void Map::createLastDoor(float x, float y, float width, float height, int coordX, int coordY) {
	auto newLastDoor = std::make_shared<Door>(x, y, width, height, 2);
	allDoors.push_back(newLastDoor);
	mapElementsCoordinates[{coordX, coordY}] = newLastDoor;
}

void Map::createNPC(float x, float y, float width, float height, int coordX, int coordY)
{
	auto newNPC = std::make_shared<NPC>(x, y, width, height, std::make_shared<DialogueBox>(m_font));
	allNPCs.push_back(newNPC);
	mapElementsCoordinates[{coordX, coordY}] = newNPC;
}


void Map::displayMap(sf::RenderWindow& window) {
	for (auto& wall : allWalls) {
		wall->draw(window);
	}
	for (auto& door : allDoors) {
		door->draw(window);
	}
	for (auto& button : allButtons) {
		button->draw(window);
	}

	for (auto& npc : allNPCs) {
		npc->draw(window);
	}
	for (auto& terminal : allTerminals) {
		terminal->draw(window);
	}
	for (auto& stain : allStains) {
		stain->draw(window);
	}
}

std::vector<std::shared_ptr<MapElements>>& Map::getAllWalls()
{
	return allWalls;
}

std::vector<std::shared_ptr<MapElements>>& Map::getAllDoors()
{
	return allDoors;
}

std::vector<std::shared_ptr<MapElements>>& Map::getAllButtons()
{
	return allButtons;
}

std::vector<std::shared_ptr<MapElements>>& Map::getAllNPCs()
{
	return allNPCs;
}

std::vector<std::shared_ptr<MapElements>>& Map::getAllTerminals()
{
	return allTerminals;
}

std::vector<std::shared_ptr<MapElements>>& Map::getAllStains()
{
	return allStains;
}

bool Map::isSolid(int coordX, int coordY)
{
	//for (auto& pair : mapElementsCoordinates)
	//{
		//std::cout << "[" << pair.first.x << ", " << pair.first.y << "]" << ":\t" << pair.second->id << std::endl;
	//}

	//std::cout << "Coords vector: " << coordX << ", " << coordY << std::endl;
	if (mapElementsCoordinates.at(sf::Vector2i( coordX, coordY )) != nullptr)
	{
		return mapElementsCoordinates[{coordX, coordY}]->isWalkable();
	}
	else
	{
		//std::cout << "ELEMENT NOT FOUND\n";
		return false;
	}
}

std::string Map::getCode()
{
	return m_code;

}