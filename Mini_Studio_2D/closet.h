#pragma once
#include "entity.h"
#include "player.h"

class Closet : public Entity{
public:
	Closet(int s, int h, Map& map);

	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	void push(Player& player);
	void anim(float deltaTime) override;
};

