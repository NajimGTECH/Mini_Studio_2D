#include "shelf.h"

Shelf::Shelf(int s, int h, Map& map) : Entity(s, h, map){
	m_texture.loadFromFile("Assets/Fournitures/shelf.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(100, 200);
	m_sprite.setScale(2, 2);
}

void Shelf::update(float deltaTime) {}

void Shelf::draw(sf::RenderWindow& window) {
	window.draw(m_sprite);
}

void Shelf::anim(float deltaTime)
{
}