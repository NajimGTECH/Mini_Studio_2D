#pragma once
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

class MapElements
{
public:
  MapElements(float x, float y, float width, float height, int);
  virtual ~MapElements() {} 

	
	sf::RectangleShape shape;
	bool opened = false;

	int id;
	bool isTransparent = true;
	float x, y, width, height;



	virtual void draw(sf::RenderWindow& window); 

	void openDoor();
	void washStain();

protected:

	int m_opacity = 255;

	sf::Font m_font;
	sf::Text m_text;
};

