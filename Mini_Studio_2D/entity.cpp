#include "entity.h"

Entity::Entity(int size, int hp) : m_size(size), m_hp(hp)
{

	m_shape.setSize(sf::Vector2f(m_size, size));
	m_shape.setFillColor(sf::Color::Green);
}

sf::RectangleShape& Entity::getShape() {
	return m_shape;
}


sf::RectangleShape& Entity::getBase() {
	return m_base;
}

float Entity::getFov() const {
	return m_fov;
}

float Entity::getOrientation() const {
	return m_orientation;
}

float Entity::setOrientation(float orientation) {
	m_orientation = orientation;
	return m_orientation;
}