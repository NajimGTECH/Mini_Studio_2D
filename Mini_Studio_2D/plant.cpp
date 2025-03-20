#include "plant.h"

Plant::Plant(float x_, float y_, float width_, float height_, int id_)
{

	id = id_; x = x_; y = y_; height = height_; width = width_ * 2;

	m_mass = 200.f;

	m_texture.loadFromFile("Assets/Furnitures/plant.png");
	shape.setSize({ width_ * 1, height_ * 2 });
	shape.setPosition({ x_, y_ });

	m_sprite.setTexture(m_texture);
	m_sprite.setScale({ shape.getSize().x / m_texture.getSize().x , shape.getSize().y / m_texture.getSize().y });
	m_sprite.setPosition(shape.getPosition());
}

void Plant::update(float deltaTime)
{
	m_sprite.setPosition(shape.getPosition());
	//m_gravity.applyGravity(this, deltaTime);
}

void Plant::draw(sf::RenderWindow& window)
{
	//window.draw(m_shape);
	window.draw(m_sprite);
}

/*
void Desk::push(Player& player) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		if (player.getWalkSide()) {
			m_shape.move(1, 0);
		}
		else {
			m_shape.move(-1, 0);
		}
	}
}*/

void Plant::anim(float deltaTime)
{
}