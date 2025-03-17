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
	allStains.clear();

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

		case 'N': createNPC(x, y, 60, 60); x += 60; i++; break;

		case 'T': createTerminal(x, y, 60, 60); x += 60; i++; break;
		case 'P': createLastDoor(x, y, 60, 60); x += 60; i++; break;
		case ' ': x += 60; i++; break;

		//Stains:
		case '~': createStain(x, y, 60, 60, ""); x += 60; i++; break;
		case '0': createStain(x, y, 60, 60, "0"); x += 60; i++; break;
		case '1': createStain(x, y, 60, 60, "1"); x += 60; i++; break;
		case '2': createStain(x, y, 60, 60, "2"); x += 60; i++; break;
		case '3': createStain(x, y, 60, 60, "3"); x += 60; i++; break;
		case '4': createStain(x, y, 60, 60, "4"); x += 60; i++; break;
		case '5': createStain(x, y, 60, 60, "5"); x += 60; i++; break;
		case '6': createStain(x, y, 60, 60, "6"); x += 60; i++; break;
		case '7': createStain(x, y, 60, 60, "7"); x += 60; i++; break;
		case '8': createStain(x, y, 60, 60, "8"); x += 60; i++; break;
		case '9': createStain(x, y, 60, 60, "9"); x += 60; i++; break;

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
 
void Map::createStain(float x, float y, float width, float height, std::string text)
{
	allStains.push_back(std::make_shared<Stain>(x, y, width, height, text));
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

void Map::createNPC(float x, float y, float width, float height) {
	allNPCs.push_back(std::make_shared<NPC>(x, y, width, height, *dialogueBox));
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
}

void Map::setDialogueBox(DialogueBox* db) {
	dialogueBox = db;

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

std::vector<std::shared_ptr<MapElements>>& Map::getAllTerminals()
{
	return allTerminals;
}

std::vector<std::shared_ptr<MapElements>>& Map::getAllStains()
{
	return allStains;
}

std::string Map::getCode()
{
	return m_code;

}
