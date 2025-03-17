#pragma once
#include "entity.h"
class Lamp : public Entity{
public:
	Lamp(sf::Vector2f s, int h, Map& map);
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	void illuminate();
	void anim(float deltaTime) override;
};

