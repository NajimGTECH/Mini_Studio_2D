#include "entityManager.h"

EntityManager::EntityManager() {
	player = std::make_shared<Player>(100, 10);
}



void EntityManager::CollideCheck(Map& map, float deltaTime) {
	for (auto& wall : map.getAllWalls()) {
		if (player->getBase().getGlobalBounds().intersects(wall->shape.getGlobalBounds())) {
			player->getYVelocity().y = -9.81f * 50 * deltaTime;
		}

		if (player->direction == 1) {
			if (player->getShape().getGlobalBounds().intersects(wall->shape.getGlobalBounds())) {
				player->getShape().setPosition(player->getShape().getPosition().x -6 , player->getShape().getPosition().y);
			}
		}
		if (player->direction == 2) {
			if (player->getShape().getGlobalBounds().intersects(wall->shape.getGlobalBounds())) {
				player->getShape().setPosition(player->getShape().getPosition().x +6 , player->getShape().getPosition().y);
			}
		}
	}
	for (auto& door : map.getAllDoors()) {
		if (player->getBase().getGlobalBounds().intersects(door->shape.getGlobalBounds())) {
			player->getYVelocity().y = -9.81f * 50 * deltaTime;
		}

		if (player->direction == 1) {
			if (player->getShape().getGlobalBounds().intersects(door->shape.getGlobalBounds())) {
				player->getShape().setPosition(player->getShape().getPosition().x - 6, player->getShape().getPosition().y);
			}
		}
		if (player->direction == 2) {
			if (player->getShape().getGlobalBounds().intersects(door->shape.getGlobalBounds())) {
				player->getShape().setPosition(player->getShape().getPosition().x + 6, player->getShape().getPosition().y);
			}
		}
	}
}