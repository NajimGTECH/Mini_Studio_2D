#pragma once
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

//#include "gravity.h"

class MapElements
{
public:
  MapElements(float x, float y, float width, float height, int);
  MapElements();

  virtual ~MapElements() {} 

	
	sf::RectangleShape shape;
	bool opened = false;

	int id;
	float x, y, width, height;

	virtual void draw(sf::RenderWindow& window); 
	virtual void update(float deltaTime); 
	
	void openDoor();
	void washStain();
	bool isWalkable();

	float getMass();

protected:

	//Gravity m_gravity;

	int m_opacity = 255;
	float m_mass = 100.f;

	sf::Font m_font;
	sf::Text m_text;
};

struct Vector2iHash {
	std::size_t operator()(const sf::Vector2i& vec) const {
		std::size_t hash_x = std::hash<int>{}(vec.x);

		return hash_x;
	}
};