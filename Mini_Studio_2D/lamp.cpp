#include "lamp.h"

Lamp::Lamp(sf::Vector2f s, int h, Map& map) : Entity(s, h, map) {
	m_shape.setSize(sf::Vector2f(50, 100));
	m_shape.setFillColor(sf::Color::Yellow);
}

void Lamp::update(float deltaTime) {}

void Lamp::draw(sf::RenderWindow& window) {
	window.draw(m_shape);
}

void Lamp::illuminate() {
}

void Lamp::anim(float deltaTime)
{
}