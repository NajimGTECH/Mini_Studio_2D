#pragma once
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

class MapElements
{
public:
	sf::RectangleShape shape;
	bool opened = false;

	int id;

	float x, y, width, height;

	MapElements(float x, float y, float width, float height, int);
	void draw(sf::RenderWindow& window);

	void openDoor();
	void washStain();

protected:

	int m_opacity = 255;

	sf::Font m_font;
	sf::Text m_text;
};

