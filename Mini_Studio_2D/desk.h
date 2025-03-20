#pragma once
#include "entity.h"
#include "player.h"
class Desk : public Entity{
public:
	Desk(sf::Vector2f s, int h, Map& map);
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	void push(Player& player);
	void anim(float deltaTime) override;
};

