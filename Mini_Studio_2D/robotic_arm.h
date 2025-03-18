#pragma once
#include "entity.h"

class RoboticArm : public Entity {
public:
	RoboticArm(sf::Vector2f s, int h, Map& map);
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	void move();
	void anim(float deltaTime) override;
};

