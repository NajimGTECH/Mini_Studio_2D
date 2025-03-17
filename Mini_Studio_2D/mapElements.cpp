#include "mapElements.h"

MapElements::MapElements(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) 
{
	if (!m_font.loadFromFile("Assets/Fonts/HelpMe.ttf"))
	{
		std::cout << "Couldn't load map elements font!\n";
	}
	m_text.setFont(m_font);
	m_text.setCharacterSize(40);
	m_text.setFillColor(sf::Color::White);
}

void MapElements::draw(sf::RenderWindow& window) {
	window.draw(m_text);
	window.draw(shape);
}

void MapElements::openDoor() {
	std::cout << "door is open" << std::endl;
	shape.move(0, -200);
}

void MapElements::washStain()
{
	m_opacity -= .5f;

	if (m_opacity <= 0)
		m_opacity = 0;

	shape.setFillColor(sf::Color(190, 95, 30, m_opacity));
}