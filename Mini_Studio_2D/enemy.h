#pragma once
#include "entity.h"

class Enemy : public Entity
{
public:
	
	Enemy(sf::Vector2f size, int hp, Map& map);

	void update(float deltaTime) override;

	void draw(sf::RenderWindow window);

	void anim(float deltaTime) override;

};

