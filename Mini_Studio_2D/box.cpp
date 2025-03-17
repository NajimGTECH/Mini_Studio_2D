#include "box.h"

Box::Box(sf::Vector2f s, int h, Map& map) : Entity(s, h, map){
	m_shape.setSize(sf::Vector2f(70, 70));
	m_shape.setFillColor(sf::Color::Cyan);
}

void Box::update(float deltaTime){}

void Box::draw(sf::RenderWindow& window){
	window.draw(m_shape);
}

void Box::anim(float deltaTime)
{
}
