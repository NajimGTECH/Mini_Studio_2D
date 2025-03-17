#pragma once
#include "entity.h"
class Closet : public Entity{
public:
	Closet(int s, int h, Map& map);
	void update();
	void draw(sf::RenderWindow& window);
	void anim(float deltaTime) override;
};

