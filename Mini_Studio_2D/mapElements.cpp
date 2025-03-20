#include "mapElements.h"

MapElements::MapElements(float x_, float y_, float width_, float height_, int id_) : x(x_), y(y_), width(width_), height(height_), id(id_)
{
	if (!m_font.loadFromFile("Assets/Fonts/HelpMe.ttf"))
	{
		std::cout << "Couldn't load map elements font!\n";
	}
	m_text.setFont(m_font);
	m_text.setCharacterSize(40);
	m_text.setFillColor(sf::Color::White);
}

MapElements::MapElements() : x(0), y(0), width(0), height(0), id(0)
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

void MapElements::update(float deltaTime)
{
	//nothing here
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

bool MapElements::isWalkable() {
	if (m_opacity >= 255)
	{
		return true;
	}
	return false;
}

float MapElements::getMass()
{
	return m_mass;
}
