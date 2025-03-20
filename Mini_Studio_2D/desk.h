#pragma once
#include "mapElements.h"
//#include "player.h"

class Desk : public MapElements 
{
public:
	Desk(float x, float y, float width, float height, int id);

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

	//void push(Player& player);

	void anim(float deltaTime);

private:

	sf::RectangleShape m_shape;

	sf::Texture m_texture;
	sf::Sprite m_sprite;
};

