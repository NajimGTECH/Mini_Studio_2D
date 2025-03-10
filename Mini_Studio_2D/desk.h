#pragma once
#include "entity.h"
class Desk : public Entity{
public:
	Desk(int s, int h);
	void update() override;
	void draw(sf::RenderWindow& window) override;
};

