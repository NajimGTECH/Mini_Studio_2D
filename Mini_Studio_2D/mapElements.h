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
	float x, y, width, height;

	virtual void draw(sf::RenderWindow& window); 
	
	void openDoor();
	void washStain();
	bool isWalkable();

protected:

	int m_opacity = 255;

	sf::Font m_font;
	sf::Text m_text;
};

struct Vector2iHash {
	std::size_t operator()(const sf::Vector2i& vec) const {
		std::size_t hash_x = std::hash<int>{}(vec.x);

		return hash_x;
	}
};