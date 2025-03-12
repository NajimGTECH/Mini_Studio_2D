#pragma once
#include "entity.h"
class Lamp : public Entity{
public:
	Lamp(int s, int h);
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	void illuminate();
};

