#pragma once
#include "entity.h"
class Shelf : public Entity{
public:
	Shelf(int s, int h);
	void update() override;
	void draw(sf::RenderWindow& window) override;
};

