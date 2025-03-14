#include "bookShelf.h"

BookShelf::BookShelf(int s, int h, Map& map) : Entity(s, h, map) {
	m_texture.loadFromFile("Assets/Fournitures/bookShelf.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(0.3f, 0.3f);
	m_sprite.setPosition(100, 300);
}

void BookShelf::update(float deltaTime) {}

void BookShelf::draw(sf::RenderWindow& window) {
	window.draw(m_sprite);
}

void BookShelf::Push(Player& player) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		if (player.getWalkSide()) {
			m_shape.move(1, 0);
		}
		else {
			m_shape.move(-1, 0);
		}
	}
}
