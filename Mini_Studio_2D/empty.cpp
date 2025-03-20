#include "empty.h"

Empty::Empty(float x, float y, float width, float height, int type) : MapElements(x, y, width, height, type)
{
	shape.setPosition(x, y);
	shape.setSize(sf::Vector2f(width, height));
	shape.setFillColor(sf::Color::Black);
}
