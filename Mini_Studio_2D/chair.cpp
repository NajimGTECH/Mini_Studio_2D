#include "chair.h"

Chair::Chair(sf::Vector2f size, int h, Map& map) : Entity(size, h, map){
	m_texture.loadFromFile("Assets/Fournitures/chair.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(0.3f, 0.3f);
	m_sprite.setPosition(100, 100);
}

void Chair::update(float deltaTime) {
}

void Chair::draw(sf::RenderWindow& window) {
	window.draw(m_sprite);
}

void Chair::push(Player& player) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		if (player.getWalkSide()) {
			m_shape.move(2, 0);
		}
		else {
			m_shape.move(-2, 0);
		}
	}
}

void Chair::anim(float deltaTime){}