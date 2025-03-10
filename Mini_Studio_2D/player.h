#pragma once
#include "entity.h"
#include "gravity.h"

class Player : public Entity
{
private:
	bool jumped = false;
	Gravity gravity;
public:
	
	Player(int s, int h);

	void update() override;
	void draw(sf::RenderWindow& window) override;
	void jump();
};

