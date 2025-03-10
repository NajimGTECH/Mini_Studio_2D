#include "box.h"

Box::Box(int s, int h) : Entity(s, h){
	shape.setSize(sf::Vector2f(70, 70));
	shape.setFillColor(sf::Color::Cyan);
}

void Box::update(){}

void Box::draw(sf::RenderWindow& window){
	window.draw(shape);
}