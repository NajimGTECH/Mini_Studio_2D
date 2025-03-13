#pragma once
#include "entity.h"

class WaterJet : public Entity {
public:
	WaterJet(int s, int h, Map& map);
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	void move();
};

