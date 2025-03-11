#pragma once

#include <SFML/Graphics.hpp>

#include "map.h"

class Entity
{
public:

	Entity(int size, int hp, Map& map);

	virtual void update(float deltaTime) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

	sf::RectangleShape& getShape();
	sf::RectangleShape& getBase();

	bool isCollisionDetected(sf::Vector2f targetVelocity);

protected:

	sf::RectangleShape m_shape;
	sf::RectangleShape m_base;
	int m_size;
	int m_hp;

	Map& m_map;
};

