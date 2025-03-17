#pragma once
#include "entity.h"

class RoboticArm : public Entity {
public:
	RoboticArm(int s, int h, Map& map);
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	void move();
};

