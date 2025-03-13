#include "entityManager.h"

EntityManager::EntityManager(Map& map) {
	player = std::make_shared<Player>(100, 10, map);
}

void EntityManager::addNPC(sf::Vector2f position, Map& map) {
	npcs.push_back(std::make_shared<NPC>(50, 10, map, position));
}

void EntityManager::drawNPCs(sf::RenderWindow& window) {
	for (auto& npc : npcs) {
		npc->draw(window);
	}
}


void EntityManager::ButtonCheck(Map& map, float deltaTime) {
	for (auto& button : map.getAllButtons()) {
		if (player->getBase().getGlobalBounds().intersects(button->shape.getGlobalBounds())) {
			for (auto& door : map.getAllDoors()) {
				door->openDoor();
			}
			map.getAllButtons().clear();
		}
	}
}