#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class MapElements
{
public:
	sf::RectangleShape shape;

	float x, y, width, height;

	MapElements(float x, float y, float width, float height);
	virtual void draw(sf::RenderWindow& window); 
	virtual ~MapElements() {} 

	void openDoor();
};

