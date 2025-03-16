#include "map.h"

Map::Map() {}


void Map::createMap(int lvl) {
	m_mapFile.close();
	m_codeFile.close();
	m_mapFile.open("map" + std::to_string(lvl) + ".txt");
	m_codeFile.open("codes.txt");

	allWalls.clear();
	allButtons.clear();
	allDoors.clear();
	allTerminals.clear();

	int i = 0, x = 0, y = 0, j = 0;
	char ch;

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
		if (currentLine == lvl) {  // Si on atteint la ligne du niveau demandé
			m_code = line;
			std::cout << "got it" << std::endl;
			break;
		}
	}


	std::cout << m_code << " est le code" << std::endl;


	while (m_mapFile.get(ch)) {
		switch (ch)
		{
		case '#': createWall(x, y, 60, 60);x += 60; i++; break;
		case 'D': createDoor(x, y, 60, 60); x += 60; i++; break;
		case 'B': createButton(x, y, 60, 60); x += 60; i++; break;
		case 'T': createTerminal(x, y, 60, 60); x += 60; i++; break;
		case 'P': createLastDoor(x, y, 60, 60); x += 60; i++; break;
		case ' ': x += 60; i++; break;
		}


		if (i == 32) {
			y += 60; x = 0; i = 0; j++;
		}

		if (j == 18) {
			y = 0; x = 0; i = 0; j++;
		}
	}
}

void Map::createTerminal(float x, float y, float width, float height) {
	allTerminals.push_back(std::make_shared<Terminal>(x, y, width, height, 2));
}

void Map::createWall(float x, float y, float width, float height) {
	allWalls.push_back(std::make_shared<Wall>(x, y, width, height, 0));
}

void Map::createDoor(float x, float y, float width, float height) {
	allDoors.push_back(std::make_shared<Door>(x, y, width, height, 1));
}

void Map::createButton(float x, float y, float width, float height) {
	allButtons.push_back(std::make_shared<Button>(x, y, width, height, 1));
}

void Map::createLastDoor(float x, float y, float width, float height) {
	allDoors.push_back(std::make_shared<Door>(x, y, width, height, 2));
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
	for (auto& terminal : allTerminals) {
		terminal->draw(window);
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

std::vector<std::shared_ptr<MapElements>>& Map::getAllTerminals()
{
	return allTerminals;
}

std::string Map::getCode()
{
	return m_code;
}
