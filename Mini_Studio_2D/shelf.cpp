#include "shelf.h"

Shelf::Shelf(int s, int h) : Entity(s, h){
	shape.setSize(sf::Vector2f(500, 100));
	shape.setFillColor(sf::Color::Green);
}

void Shelf::update() {}

void Shelf::draw(sf::RenderWindow& window) {
	window.draw(shape);
}