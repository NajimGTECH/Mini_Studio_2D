#pragma once
#include "entity.h"

class Player : public Entity
{
private:

public:
	
	Player(int s, int h);

	void update() override;
	void draw(sf::RenderWindow& window) override;
};

