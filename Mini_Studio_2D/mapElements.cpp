#include "mapElements.h"

MapElements::MapElements(float x, float y, float width, float height, int id) : x(x), y(y), width(width), height(height), id(id) {}

void MapElements::draw(sf::RenderWindow& window) {
	window.draw(shape);
}

void MapElements::openDoor() {
	std::cout << "door is open" << std::endl;
	shape.move(0, -200);
}