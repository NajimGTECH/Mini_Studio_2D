#pragma once

#include <SFML/Graphics.hpp>

class Entity
{
protected:
	sf::RectangleShape shape;
	int size;
	int hp;
public:
	Entity(int s, int h);
	virtual void update() = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	sf::RectangleShape& getShape();
};

