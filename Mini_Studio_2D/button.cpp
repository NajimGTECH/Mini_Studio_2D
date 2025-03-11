#include "button.h"

Button::Button(float x, float y, float width, float height) : MapElements(x, y, width, height) {
	shape.setPosition(x, y);
	shape.setSize(sf::Vector2f(width, height));
	shape.setFillColor(sf::Color::Red);
}