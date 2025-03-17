#include "stain.h"

Stain::Stain(float x, float y, float width, float height) : MapElements(x, y, width, height, -1) {
	shape.setPosition(x, y);
	shape.setSize(sf::Vector2f(width, height));
	shape.setFillColor(sf::Color(190, 95, 30, m_opacity));

	m_text.setPosition(shape.getPosition() + shape.getSize() / 4.f);
	m_text.setString("");
}

Stain::Stain(float x, float y, float width, float height, std::string text) : MapElements(x, y, width, height, -1) {
	shape.setPosition(x, y);
	shape.setSize(sf::Vector2f(width, height));
	shape.setFillColor(sf::Color(190, 95, 30, m_opacity));

	m_text.setPosition(shape.getPosition() + shape.getSize() / 4.f);
	m_text.setString(text);
}
