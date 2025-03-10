#include "lamp.h"

Lamp::Lamp(int s, int h) : Entity(s, h) {
	m_shape.setSize(sf::Vector2f(50, 70));
	m_shape.setFillColor(sf::Color::Yellow);
}

void Lamp::update() {
}

void Lamp::draw(sf::RenderWindow& window) {
	window.draw(m_shape);
}

void Lamp::illuminate() {
	
}
