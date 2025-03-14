#pragma once
#include "entity.h"
#include "player.h"

class Chair : Entity{
public:
	Chair(int s, int h, Map& map);
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	void push(Player& player);
};

