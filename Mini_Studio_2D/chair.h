#pragma once
#include "entity.h"
class Chair : Entity{
public:
	Chair(int s, int h);
	void update();
	void draw(sf::RenderWindow& window);
	void push();
};

