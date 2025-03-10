#pragma once
#include "entity.h"
class Lamp : public Entity{
public:
	Lamp(int s, int h);
	void update();
	void draw(sf::RenderWindow& window);
	void illuminate();
};

