#pragma once

#include <SFML/Graphics.hpp>

class Entity
{
public:

	Entity(int size, int hp);

	virtual void update(float deltaTime) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

	float getFov() const;
	float getOrientation() const;

	sf::RectangleShape& getShape();
	sf::RectangleShape& getBase();
	float setOrientation(float orientation);

protected:

	sf::RectangleShape m_shape;
	sf::RectangleShape m_base;
	int m_size;
	int m_hp;
	float m_fov = 60.0f;
	float m_orientation = 360.0f;
};

