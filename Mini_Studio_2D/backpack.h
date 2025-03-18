#pragma once
#include "entity.h"

class Backpack : public Entity
{
public:

	Backpack(Map& map);

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	void anim(float deltaTime);
private:
	float m_max_height = 30;
	float m_frequency = 0.7;
	sf::Clock m_clock;
};


