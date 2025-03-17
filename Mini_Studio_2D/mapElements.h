#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include <vector>

class MapElements
{
public:
	sf::RectangleShape shape;
	bool opened = false;

	float x, y, width, height;

	MapElements(float x, float y, float width, float height);
	void draw(sf::RenderWindow& window);

	void openDoor();
	void washStain();

protected:

	int m_opacity = 255;

	sf::Font m_font;
	sf::Text m_text;
};

