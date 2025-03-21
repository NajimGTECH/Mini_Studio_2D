#pragma once
#include "entity.h"
class Box : public Entity{
public:
	Box(sf::Vector2f s, int h, Map& map);

	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	
	void anim(float deltaTime) override;
};

