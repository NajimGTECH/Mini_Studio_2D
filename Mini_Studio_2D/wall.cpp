#include "wall.h"

Wall::Wall(float x, float y, float width, float height, int id) : MapElements(x, y, width, height, id) {
	shape.setPosition(x, y);
	shape.setSize(sf::Vector2f(width, height));
	shape.setFillColor(sf::Color::White);
}