#include "entity.h"

Entity::Entity(int s, int h) : size(s), hp(h)
{
	shape.setSize(sf::Vector2f(size, size));
	shape.setFillColor(sf::Color::Green);
}

sf::RectangleShape& Entity::getShape() {
	return shape;
}

sf::RectangleShape& Entity::getBase() {
	return base;
}