#include "backpack.h"

Backpack::Backpack(Map& map) : Entity(sf::Vector2f(50,50), 0, map) {
	if(!m_texture.loadFromFile("Assets/Player/sac_2d.png")) return;
	m_sprite.setTexture(m_texture);
	
	m_sprite.setPosition(800, 600);
}

void Backpack::draw(sf::RenderWindow& window) {
	window.draw(m_sprite);
}

void Backpack::update(float deltaTime) {
	anim(deltaTime);
	std::cout << m_sprite.getPosition().x << ' ' << m_sprite.getPosition().y << std::endl;
}

void Backpack::anim(float deltaTime) {
	float time = m_clock.getElapsedTime().asSeconds();
	float yOffset = m_max_height * std::sin(m_frequency * time * 2 * 3.14159);

	m_sprite.setPosition(800, 800 - yOffset);
}