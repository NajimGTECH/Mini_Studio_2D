#include "entityManager.h"

EntityManager::EntityManager(Map& map) {
	player = std::make_shared<Player>(100, 10, map);
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