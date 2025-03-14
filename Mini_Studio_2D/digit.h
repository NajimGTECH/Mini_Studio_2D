#pragma once

#include <SFML/Graphics.hpp>

class Digit
{
public :
	bool isClicked = false;
	int value;
	sf::RectangleShape shape;
	sf::Texture texture;
	Digit(int);
};

