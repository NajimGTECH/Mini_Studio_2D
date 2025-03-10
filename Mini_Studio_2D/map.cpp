#include "map.h"

void Map::createMap() {
	mapFile.open("map.txt");
	int i = 0, x = 0, y = 0, j = 0;
	char ch;
	if (!mapFile) {
		std::cerr << "unable to open file";
	}
	while (mapFile.get(ch)) {
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
	walls.push_back(new Wall(x, y, width, height));
}

void Map::displayMap(sf::RenderWindow& window) {
	for (auto& wall : walls) {
		wall->draw(window);
	}
}