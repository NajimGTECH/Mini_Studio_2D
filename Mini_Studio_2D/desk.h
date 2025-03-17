#pragma once
#include "entity.h"
class Desk : public Entity{
public:
	Desk(sf::Vector2f s, int h, Map& map);
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	void anim(float deltaTime) override;
};

