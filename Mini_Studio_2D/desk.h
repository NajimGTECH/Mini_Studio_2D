#pragma once
#include "entity.h"
class Desk : public Entity{
public:
	Desk(int s, int h, Map& map);
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
};

