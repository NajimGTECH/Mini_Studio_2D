#pragma once
#include "entity.h"
class Closet : public Entity{
public:
	Closet(sf::Vector2f s, int h, Map& map);
	void update();
	void draw(sf::RenderWindow& window);
	void anim(float deltaTime) override;
};

