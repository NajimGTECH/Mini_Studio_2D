#pragma once

#include <memory>

#include "player.h"
#include "map.h"

class EntityManager
{
public:

	std::shared_ptr<Player> player;

	EntityManager();

	void CollideCheck(Map& map, float deltaTime);

};

