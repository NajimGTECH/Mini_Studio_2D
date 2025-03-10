#include "chair.h"

Chair::Chair(int s, int h) : Entity(s, h){
	m_shape.setSize(sf::Vector2f(50, 70));
	m_shape.setFillColor(sf::Color::Green);
}

void Chair::update() {
}

void Chair::draw(sf::RenderWindow& window) {
	window.draw(m_shape);
}

void Chair::push() {
	//while (shape.getGlobalBounds().contains(otherSprite)) {
	//		m_shape.move(1, 0);
	//}
}