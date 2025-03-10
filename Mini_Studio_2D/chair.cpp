#include "chair.h"

Chair::Chair(int s, int h) : Entity(s, h){
	shape.setSize(sf::Vector2f(50, 70));
	shape.setFillColor(sf::Color::Green);
}

void Chair::update() {
}

void Chair::draw(sf::RenderWindow& window) {
	window.draw(shape);
}

void Chair::push() {
	while ( /*shape.getGlobalBounds().contains(otherSprite)*/ ) {
			shape.move(1, 0);
	}
}