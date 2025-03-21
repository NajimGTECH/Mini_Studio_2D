#pragma once
#include "entity.h"

class Enemy : public Entity
{
public:

	Enemy(sf::Vector2f start, Map& map);

	void update(float deltaTime) override;

	void draw(sf::RenderWindow& window);

	void anim(float deltaTime) override;

	bool isMoving();

private:

	bool isMovingRight = true;
	sf::Vector2f startpos;
	sf::Vector2f endpos;
	sf::Texture texture;
};

