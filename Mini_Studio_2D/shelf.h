#pragma once
#include "entity.h"
class Shelf : public Entity{
public:
	Shelf(int s, int h, Map& map);
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
};

