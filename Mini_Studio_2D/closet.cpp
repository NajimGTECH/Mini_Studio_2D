#include "closet.h"

Closet::Closet(int s, int h, Map& map) : Entity(s, h, map) {
	m_texture.loadFromFile("Assets/Fournitures/closet.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(500, 400);
	m_sprite.setScale(0.5, 0.5);
}

void Closet::update(float deltaTime) {
}
	
void Closet::draw(sf::RenderWindow& window) {
	window.draw(m_sprite);
}

void Closet::push(Player& player) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		if (player.getWalkSide()) {
			m_shape.move(1, 0);
		}
		else {
			m_shape.move(-1, 0);
		}
	}
}
	window.draw(m_shape);
}

void Closet::anim(float deltaTime)
{
}