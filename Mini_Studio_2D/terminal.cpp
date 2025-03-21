#include "terminal.h"

Terminal::Terminal(float x, float y, float width, float height, int id) : MapElements(x, y, width, height, id) {
	if (!m_texture.loadFromFile("Assets/Terminal/terminal_cropped.png")) return;

	shape.setTexture(&m_texture);
	shape.setPosition(x, y);
	shape.setSize(sf::Vector2f(width, height));
}