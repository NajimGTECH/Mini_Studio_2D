#include "entity.h"

Entity::Entity(int s, int h) : size(s), hp(h)
{
	shape.setSize(sf::Vector2f(size, size));
	shape.setFillColor(sf::Color::Green);
}