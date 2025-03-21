#include "box.h"

Box::Box(sf::Vector2f size, int h, Map& map) : Entity(size, h, map){
	m_texture.loadFromFile("Assets/Fournitures/box.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(0.3f, 0.3f);
	m_sprite.setPosition(100, 100);
}

void Box::update(float deltaTime){}

void Box::draw(sf::RenderWindow& window){
	window.draw(m_sprite);
}

void Box::anim(float deltaTime)
{
}
