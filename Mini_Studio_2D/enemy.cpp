#include "enemy.h"

Enemy::Enemy(sf::Vector2f start, Map& map) : startpos(start), Entity(sf::Vector2f(96, 125), 1, map)
{
	m_speed = 300.f;
	m_scaling = 1;

	m_coeffAnim = sf::Vector2f(96, 124);

	std::cout << startpos.x << startpos.y;


	m_sprite.setPosition(startpos);

	if (!m_texture.loadFromFile("Assets/Ennemi/spritesheet.png")) {
		std::cerr;
	}
	

	//m_texture.loadFromFile("Assets/Ennemi/spritesheet.png");


	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(m_animVect.x * m_coeffAnim.x, m_animVect.y * m_coeffAnim.y, m_coeffAnim.x, m_coeffAnim.y));
}


void Enemy::update(float deltaTime)
{
	m_shape.setSize(sf::Vector2f(96, 124));
	m_shape.setPosition(m_sprite.getPosition());

	if (isMovingRight && isCollisionDetected(sf::Vector2f(deltaTime * m_speed, 0))) {
		isMovingRight = false;
	}
	else if (!isMovingRight && isCollisionDetected(sf::Vector2f(deltaTime * -m_speed, 0))) {
		isMovingRight = true;
	}

	if (isMovingRight) {
		m_sprite.move(1, 0);
		m_sprite.setScale(m_scaling, m_scaling);
		m_sprite.setOrigin(0, 0);
	}
	else {
		m_sprite.move(-1, 0);
		m_sprite.setScale(-m_scaling, m_scaling);
		m_sprite.setOrigin(96, 0);
	}
	m_sprite.setTextureRect(sf::IntRect(m_animVect.x * m_coeffAnim.x, m_animVect.y * m_coeffAnim.y, m_coeffAnim.x, m_coeffAnim.y));

	std::cout << isCollisionDetected(sf::Vector2f(2, 0)) << std::endl;
	anim(deltaTime);
}

void Enemy::draw(sf::RenderWindow& window)
{
	if (!m_texture.loadFromFile("Assets/Ennemi/spritesheet.png")) {
		std::cerr;
	}


	//m_texture.loadFromFile("Assets/Ennemi/spritesheet.png");


	m_sprite.setTexture(m_texture);
	window.draw(m_sprite);
}

void Enemy::anim(float deltaTime)
{
	int timeAnimation = m_animC.getElapsedTime().asMilliseconds();

	if (timeAnimation >= 150) {
		m_animVect.x++;
		m_animC.restart();
	}
	if (m_animVect.x * m_coeffAnim.x >= m_texture.getSize().x) {
		m_animVect.x = 0;
	}
}
