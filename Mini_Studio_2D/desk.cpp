#include "desk.h"

Desk::Desk(sf::Vector2f s, int h, Map& map) : Entity(s, h, map) {
	m_texture.loadFromFile("Assets/Fournitures/desk.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(500, 400);
}

void Desk::update(float deltaTime) {}

void Desk::draw(sf::RenderWindow& window) {
	window.draw(m_sprite);
}

void Desk::push(Player& player) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		if (player.getWalkSide()) {
			m_shape.move(1, 0);
		}
		else {
			m_shape.move(-1, 0);
		}
	}
}

void Desk::anim(float deltaTime)
{
}