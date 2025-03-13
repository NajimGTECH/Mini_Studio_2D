#include "map.h"

Map::Map() {}


void Map::createMap(int lvl) {
	switch (lvl)
	{
	case 1: m_mapFile.open("map1.txt"); break;
	case 2: m_mapFile.close(); m_mapFile.open("map2.txt"); break;
	}

	allWalls.clear();
	allButtons.clear();
	allDoors.clear();

	int i = 0, x = 0, y = 0, j = 0;
	char ch;
	if (!m_mapFile) {
		std::cerr << "unable to open file";
	}
	while (m_mapFile.get(ch)) {
		switch (ch)
		{
		case '#': createWall(x, y, 60, 60);x += 60; i++; break;
		case 'D': createDoor(x, y, 60, 60); x += 60; i++; break;
		case 'B': createButton(x, y, 60, 60); x += 60; i++; break;
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

void Map::createWall(float x, float y, float width, float height) {
	allWalls.push_back(std::make_shared<Wall>(x, y, width, height));
}

void Map::createDoor(float x, float y, float width, float height) {
	allDoors.push_back(std::make_shared<Door>(x, y, width, height));
}

void Map::createButton(float x, float y, float width, float height) {
	allButtons.push_back(std::make_shared<Button>(x, y, width, height));
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

bool Map::isWalkable(int x, int y) const {
	for (const auto& element : m_elements) {
		if (element->shape.getGlobalBounds().contains(x * 60, y * 60)) {
			return false;
		}
	}
	return true;
}