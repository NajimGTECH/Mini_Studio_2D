#pragma once
#include "entity.h"
class Chair : Entity{
public:
	Chair(int s, int h, Map& map);
	void update();
	void draw(sf::RenderWindow& window);
	void push();
};

