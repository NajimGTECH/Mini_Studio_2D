#pragma once
#include "entity.h"
class Box : public Entity{
public:
	Box(int s, int h);

	void update() override;
	void draw(sf::RenderWindow& window) override;
};

