#include "map.h"


Map::Map() 
{
	if (!m_font.loadFromFile("Assets/TexteMenu/SolarPunk.otf")) {
		std::cerr << "Erreur : Impossible de charger la police SolarPunk.otf" << std::endl;
	}
}


void Map::createMap(int levelIndex) {

	std::cout << levelIndex;

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
	allNPCs.clear();
	background.clear();

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
	std::vector<std::string> mapContent;
	std::string str;
	char ch;

	while (m_mapFile.get(ch)) {
			if (ch == ' ' || ch == '\n')
			{
				if (!str.empty())
				{
					mapContent.push_back(str);
					str.clear();
				}
			}
			else
			{
				str += ch;
			}

	}

	if (!str.empty()) {
		mapContent.push_back(str);
	}

	for (int y = 0; y < 17; y++)
	{
		for (int x = 0; x < 30; x++)
		{
			std::string checker = mapContent[x + 30 * y];
			sf::Vector2f spawnPos = sf::Vector2f(TILE_SIZE_PX * (float)x, TILE_SIZE_PX * (float)y);
			if (checker[0] == '#') {
				createWall(spawnPos.x, spawnPos.y, 64, 64, checker[1] - 48);
			}
			else if (checker[0] == 'D') {
				createDoor(spawnPos.x, spawnPos.y, 64, 64, checker[1] - 48);
			}
			else if (checker[0] == 'T') {
				createTerminal(spawnPos.x, spawnPos.y, 64, 64, checker[1] - 48);
			}
			else if (checker[0] == 'B') {
				createButton(spawnPos.x, spawnPos.y, 64, 64, checker[1] - 48);
			}
			else if (checker == "~") {
				createStain(spawnPos.x, spawnPos.y, 64, 64, "");
			}
			else if (checker == "N") {
				createNPC(spawnPos.x, spawnPos.y, 64, 64);
			}
			else if (checker == "0") {
				createStain(spawnPos.x, spawnPos.y, 64, 64, "0");
			}			
			else if (checker == "1") {
				createStain(spawnPos.x, spawnPos.y, 64, 64, "1");
			}
			else if (checker == "2") {
				createStain(spawnPos.x, spawnPos.y, 64, 64, "2");
			}
			else if (checker == "3") {
				createStain(spawnPos.x, spawnPos.y, 64, 64, "3");
			}
			else if (checker == "4") {
				createStain(spawnPos.x, spawnPos.y, 64, 64, "4");
			}
			else if (checker == "5") {
				createStain(spawnPos.x, spawnPos.y, 64, 64, "5");
			}
			else if (checker == "6") {
				createStain(spawnPos.x, spawnPos.y, 64, 64, "6");
			}
			else if (checker == "7") {
				createStain(spawnPos.x, spawnPos.y, 64, 64, "7");
			}
			else if (checker == "8") {
				createStain(spawnPos.x, spawnPos.y, 64, 64, "8");
			}
			else if (checker == "9") {
				createStain(spawnPos.x, spawnPos.y, 64, 64, "9");
			}
			else if (checker == ".") {
				createEmpty(spawnPos.x, spawnPos.y, 64, 64, 0);
			}
			else if (checker == "|") {
				createEmpty(spawnPos.x, spawnPos.y, 64, 64, 1);
			}
			else if (checker == "[") {
				createEmpty(spawnPos.x, spawnPos.y, 64, 64, 2);
			}
		}
	}
}

/*void Map::readMapFile()
{
	int i = 0, x = 0, y = 0, j = 0;
	char ch;
	int compte = 0;

	while (m_mapFile.get(ch)) {
		switch (ch)
		{
		case '#': createWall(x, y, 60, 60); x += 60; i++; break;
		case 'D': createDoor(x, y, 60, 60); x += 60; i++; break;
		case 'B': createButton(x, y, 60, 60); x += 60; i++; break;

		case 'N': createNPC(x, y, 60, 60); x += 60; i++; break;

		case 'T': createTerminal(x, y, 60, 60); x += 60; i++; break;
		case 'P': createLastDoor(x, y, 60, 60); x += 60; i++; break;
		case ' ': x += 60; i++; break;
		case 'E': x += 60; i++; break;

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
		compte++;
	}

	std::cout << "mapsizeM" << compte;
}*/

void Map::createTerminal(float x, float y, float width, float height, int type) {
	allTerminals.push_back(std::make_shared<Terminal>(x, y, width, height, type));
}
 
void Map::createStain(float x, float y, float width, float height, std::string text)
{
	allStains.push_back(std::make_shared<Stain>(x, y, width, height, text));
}

void Map::createEmpty(float x, float y, float width, float height, int type)
{
	background.push_back(std::make_shared<Empty>(x, y, width, height, type));
}

void Map::createWall(float x, float y, float width, float height, int type) {
	allWalls.push_back(std::make_shared<Wall>(x, y, width, height, type));
}

void Map::createDoor(float x, float y, float width, float height, int type) {
	allDoors.push_back(std::make_shared<Door>(x, y, width, height, type));
}

void Map::createButton(float x, float y, float width, float height, int type) {
	allButtons.push_back(std::make_shared<Button>(x, y, width, height, type));
}

void Map::createNPC(float x, float y, float width, float height) 
{
	allNPCs.push_back(std::make_shared<NPC>(x, y, width, height, std::make_shared<DialogueBox>(m_font)));
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
	for (auto& empty : background) {
		empty->draw(window);
	}
}

std::vector<std::shared_ptr<MapElements>>& Map::getAllWalls()
{
	return allWalls;
}

std::vector<std::shared_ptr<MapElements>>& Map::getBackground()
{
	return background;
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

std::string Map::getCode()
{
	return m_code;

}

std::ifstream& Map::getMapFile()
{
	return m_mapFile;
}
