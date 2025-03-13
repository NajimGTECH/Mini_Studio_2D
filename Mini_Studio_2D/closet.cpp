#include "closet.h"

Closet::Closet(int s, int h, Map& map) : Entity(s, h, map) {
	m_texture.loadFromFile("Assets/Meubles/closet.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(500, 400);
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