#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include <vector>

class MapElements
{
public:
  MapElements(float x, float y, float width, float height, int);
  virtual ~MapElements() {} 

	
	sf::RectangleShape shape;
	bool opened = false;

	int id;

	float x, y, width, height;



	virtual void draw(sf::RenderWindow& window); 
	
	


	void openDoor();
	void washStain();

protected:

	int m_opacity = 255;

	sf::Font m_font;
	sf::Text m_text;
};

