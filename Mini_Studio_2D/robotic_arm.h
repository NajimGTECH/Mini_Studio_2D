#pragma once
#include "entity.h"*

class RoboticArm : public Entity {
public:
	RoboticArm(int s, int h);
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	void move()
};

