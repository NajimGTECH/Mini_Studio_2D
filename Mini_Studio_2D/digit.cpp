#include "digit.h"

Digit::Digit(int v, int t) : value(v), type(t) {
	shape.setSize(sf::Vector2f(110, 110));
}