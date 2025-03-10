#include "shelf.h"

Shelf::Shelf(int s, int h) : Entity(s, h){
	m_shape.setSize(sf::Vector2f(500, 100));
	m_shape.setFillColor(sf::Color::Green);
}

void Shelf::update(float deltaTime) {}

void Shelf::draw(sf::RenderWindow& window) {
	window.draw(m_shape);
}