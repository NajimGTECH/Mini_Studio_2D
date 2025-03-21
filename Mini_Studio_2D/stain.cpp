#include "stain.h"

Stain::Stain(float x, float y, float width, float height) : MapElements(x, y, width, height, 0) {

	int i;
	i = rand() % 2;

	if (!m_texture.loadFromFile("Assets/Furnitures/stain1.png")) return;

	shape.setTexture(&m_texture);

	shape.setPosition(x, y);
	shape.setSize(sf::Vector2f(width, height));
	shape.setFillColor(sf::Color(255, 255, 255, m_opacity));

	m_text.setPosition(shape.getPosition() + shape.getSize() / 4.f);
	m_text.setString("");
}

Stain::Stain(float x, float y, float width, float height, std::string text) : MapElements(x, y, width, height, 0) {

	int i;
	i = rand() % 2;


	if (!m_texture.loadFromFile("Assets/Furnitures/stain" + std::to_string(i) + ".png")) return;
	shape.setTexture(&m_texture);

	

	shape.setPosition(x, y);
	shape.setSize(sf::Vector2f(width, height));
	shape.setFillColor(sf::Color(255, 255, 255, m_opacity));

	m_text.setPosition(shape.getPosition() + shape.getSize() / 4.f);
	m_text.setString(text);
}
