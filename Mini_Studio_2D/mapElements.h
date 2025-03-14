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
};

