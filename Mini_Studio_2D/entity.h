#pragma once

#include <SFML/Graphics.hpp>

class Entity
{
protected:
	sf::RectangleShape shape;
	int size;
	int hp;
public:

	Entity(int size, int hp);

	virtual void update(float deltaTime) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

	sf::RectangleShape& getShape();
	sf::RectangleShape& getBase();

protected:

	sf::RectangleShape m_shape;
	int m_size;
	int m_hp;
};

