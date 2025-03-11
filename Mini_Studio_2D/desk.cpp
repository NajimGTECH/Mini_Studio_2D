#include "desk.h"

Desk::Desk(int s, int h, Map& map) : Entity(s, h, map) {
	m_shape.setSize(sf::Vector2f(200, 100));
	m_shape.setFillColor(sf::Color::Red);
}

void Desk::update(float deltaTime) {}

void Desk::draw(sf::RenderWindow& window) {
	window.draw(m_shape);
}
