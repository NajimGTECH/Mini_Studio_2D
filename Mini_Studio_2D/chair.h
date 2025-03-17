#pragma once
#include "entity.h"
class Chair : Entity{
public:
	Chair(int s, int h, Map& map);
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	void push();
	void anim(float deltaTime) override;
};

