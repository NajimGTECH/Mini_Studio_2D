#pragma once

#include <memory>
#include <vector>
#include "npc.h"
#include "player.h"
#include "map.h"

class EntityManager
{
public:

	std::shared_ptr<Player> player;
	std::vector<std::shared_ptr<NPC>> npcs;

	EntityManager(Map& map);

	void ButtonCheck(Map& map, float deltaTime);
	void addNPC(sf::Vector2f position, Map& map);
	void drawNPCs(sf::RenderWindow& window);

};

