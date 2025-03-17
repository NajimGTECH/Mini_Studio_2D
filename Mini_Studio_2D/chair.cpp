#include "chair.h"

Chair::Chair(sf::Vector2f s, int h, Map& map) : Entity(s, h, map){
	m_shape.setSize(sf::Vector2f(50, 70));
	m_shape.setFillColor(sf::Color::Green);
}

void Chair::update(float deltaTime) {
}

void Chair::draw(sf::RenderWindow& window) {
	window.draw(m_shape);
}

void Chair::push() {
	//while (shape.getGlobalBounds().contains(otherSprite)) {
	//		m_shape.move(1, 0);
	//}
}

void Chair::anim(float deltaTime)
{
}