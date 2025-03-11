#include "entityManager.h"

EntityManager::EntityManager(Map& map) {
	player = std::make_shared<Player>(100, 10, map);
}

void EntityManager::CollideCheck(Map& map, float deltaTime) {
/*
	bool isPlayerGrounded = false;
	bool isTopHit = false;

	Gravity referenceGravity;

	for (auto& wall : map.getMapElements()) {

		if (player->getBase().getGlobalBounds().intersects(wall->shape.getGlobalBounds())) 
		{
			isPlayerGrounded = true;
		}



		//std::cout << "Plr velocity: " << player->getYVelocity().x << ", " << player->getYVelocity().y << "Gravity: " << 

		if (player->getShape().getGlobalBounds().intersects(wall->shape.getGlobalBounds()))
		{

			if (player->direction == 1)
			{
				player->getShape().setPosition(player->getShape().getPosition().x - (deltaTime * player->getSpeed()), player->getShape().getPosition().y);
			}
			else if (player->direction == -1)
			{
				player->getShape().setPosition(player->getShape().getPosition().x + (deltaTime * player->getSpeed()), player->getShape().getPosition().y);
			}

		}
	}

	if (isTopHit)
	{
		player->setYVelocity({ 0.f, 0.f });
		return;
	}

	if (isPlayerGrounded == false) {

		

		if (player->isJumping() == false)
		{
			player->setYVelocity({ 0.f, 0.f });
		}
		
	}
	else
	{
		if (player->isJumping() == false)
		{
			player->setYVelocity({ 0.f, -referenceGravity.getForce() * deltaTime });
		}
	}*/
}