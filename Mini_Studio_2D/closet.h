#pragma once
#include "mapElements.h"
//#include "player.h"

class Closet : public MapElements
{
public:
	Closet(float x, float y, float width, float height, int id);

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

	//void push(Player& player);

	void anim(float deltaTime);

private:

	sf::Texture m_texture;
	sf::Sprite m_sprite;
};
