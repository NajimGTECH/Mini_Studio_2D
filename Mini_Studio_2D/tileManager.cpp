#include "tileManager.h"



TileManager::TileManager()
{
	if (!m_tileSet.loadFromFile("Assets/Tiles/tileset.png")) return;

}

void TileManager::applyTileSet(Map& map)
{

	for (auto wall : map.getAllWalls()) {
		wall->shape.setTexture(&m_tileSet);
		if (wall->id == 0) {
			wall->shape.setTextureRect(sf::IntRect(224, 112, 64, 64));
		}
		if (wall->id == 1) {
			wall->shape.setTextureRect(sf::IntRect(32, 352, 64, 64));
		}
		if (wall->id == 2) {
			wall->shape.setTextureRect(sf::IntRect(32, 272, 64, 64));
		}
		if (wall->id == 3) {
			wall->shape.setTextureRect(sf::IntRect(32, 272, 64, 64));
			wall->shape.setRotation(180);
			wall->shape.setOrigin(64, 64);
		}
		if (wall->id == 4) {
			wall->shape.setTextureRect(sf::IntRect(416, 272, 64, 64));
		}
		if (wall->id == 5) {
			wall->shape.setTextureRect(sf::IntRect(224, 192, 64, 64));
		}
	}

	for (auto empty : map.getBackground()) {
		empty->shape.setTexture(&m_tileSet);
		empty->shape.setFillColor(sf::Color(255, 255, 255, 100));
		if (empty->id == 0) {
			//empty->shape.setTextureRect(sf::IntRect(416, 432, 64, 64));
			empty->shape.setFillColor(sf::Color(255, 255, 255, 0));
		}
		if (empty->id == 1) {
			empty->shape.setTextureRect(sf::IntRect(128, 32, 64, 64));
			empty->shape.setScale(8, 8);
		}
		if (empty->id == 2) {
			empty->shape.setTextureRect(sf::IntRect(320, 32, 64, 64));
			empty->shape.setScale(6, 6);
		}
	}
}
