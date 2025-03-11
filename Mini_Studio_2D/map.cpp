#include "map.h"

void Map::createMap() {
	m_mapFile.open("map.txt");
	int i = 0, x = 0, y = 0, j = 0;
	char ch;
	if (!m_mapFile) {
		std::cerr << "unable to open file";
	}
	while (m_mapFile.get(ch)) {
		switch (ch)
		{
		case '#': createWall(x, y, 60, 60);x += 60; i++; break;
	

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
	m_elements.push_back(std::make_shared<Wall>(x, y, width, height));
}

void Map::displayMap(sf::RenderWindow& window) {
	for (auto& wall : m_elements) {
		wall->draw(window);
	}
}

std::ifstream& Map::getMapFile(){
	return m_mapFile;
}

std::vector<std::shared_ptr<MapElements>>& Map::getMapElements()
{
	return m_elements;
}
