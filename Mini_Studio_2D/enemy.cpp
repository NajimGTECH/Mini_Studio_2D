#include "enemy.h"

Enemy::Enemy(sf::Vector2f start, sf::Vector2f end, Map& map) : startpos(start), endpos(end), Entity(sf::Vector2f(96,125), 1, map)
{
	m_scaling = 1;

	m_coeffAnim = sf::Vector2f(96, 124);

	if (!m_texture.loadFromFile("Assets/Ennemi/spritesheet.png")) {
		return;
	}
	m_sprite.setPosition(startpos);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(m_animVect.x * m_coeffAnim.x, m_animVect.y * m_coeffAnim.y, m_coeffAnim.x, m_coeffAnim.y));
}

void Enemy::update(float deltaTime)
{
	if (isMovingRight && m_sprite.getPosition().x > endpos.x) {
		isMovingRight = false;
		
	}
	else if (!isMovingRight && m_sprite.getPosition().x < startpos.x) {
		isMovingRight = true;

	}

	if (isMovingRight) {
		m_sprite.move(1, 0);
		m_sprite.setScale(m_scaling, m_scaling);
	}
	else {
		m_sprite.move(-1, 0);
		m_sprite.setScale(-m_scaling, m_scaling);
	}
	m_sprite.setTextureRect(sf::IntRect(m_animVect.x * m_coeffAnim.x, m_animVect.y * m_coeffAnim.y, m_coeffAnim.x, m_coeffAnim.y));


	anim(deltaTime);
}

void Enemy::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

void Enemy::anim(float deltaTime)
{
	int timeAnimation = m_animC.getElapsedTime().asMilliseconds();
	
		if (timeAnimation >= 150) {
			m_animVect.x++;
			m_animC.restart();
			std::cout << m_sprite.getTextureRect().getPosition().x << ' ' << m_sprite.getTextureRect().getPosition().y << ' ' << m_animVect.x << std::endl;
		}
		if (m_animVect.x * m_coeffAnim.x >= m_texture.getSize().x) {
			m_animVect.x = 0;
		}
}
