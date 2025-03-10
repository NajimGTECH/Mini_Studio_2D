#include "closet.h"

Closet::Closet(int s, int h) : Entity(s, h) {
	m_shape.setSize(sf::Vector2f(50, 70));
	m_shape.setFillColor(sf::Color::Blue);
}

void Closet::update() {
}
	
void Closet::draw(sf::RenderWindow& window) {
	window.draw(m_shape);
}
