#include "desk.h"

Desk::Desk(int s, int h) : Entity(s, h) {
	shape.setSize(sf::Vector2f(200, 100));
	shape.setFillColor(sf::Color::Red);
}

void Desk::update() {}

void Desk::draw(sf::RenderWindow& window) {
	window.draw(shape);
}
