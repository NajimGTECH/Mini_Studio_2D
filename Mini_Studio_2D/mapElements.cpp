#include "mapElements.h"

MapElements::MapElements(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) {}

void MapElements::draw(sf::RenderWindow& window) {
	window.draw(shape);
}

void MapElements::openDoor() {
	std::cout << "door is open" << std::endl;
	shape.move(0, -100);
}