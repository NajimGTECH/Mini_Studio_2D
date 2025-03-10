#pragma once
#include "entity.h"
class Closet : public Entity{
public:
	Closet(int s, int h);
	void update();
	void draw(sf::RenderWindow& window);
};

