#include "player.h"


Player::Player(int s, int h) : Entity(s, h)
{

	m_shape.setPosition(500, 400);
	m_base.setSize(sf::Vector2f(m_shape.getSize().x - 20, 12));
	m_base.setPosition(m_shape.getPosition().x + 10, m_shape.getPosition().y + m_shape.getSize().y - 2);
}

void Player::update(float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		m_shape.move(2 * deltaTime * m_speed, 0);
		direction = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
		m_shape.move(-2 * deltaTime * m_speed, 0);
		direction = 2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {

		if (!m_hasJumped)
		std::thread(&Player::jump, this, deltaTime).detach();
	}

	m_gravity.applyGravity(this, deltaTime);
	m_shape.setPosition(m_shape.getPosition() + m_yVelocity);

	m_base.setPosition(m_shape.getPosition().x + 10, m_shape.getPosition().y + m_shape.getSize().y - 2);
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
}

void Player::jump(float deltaTime) 
{
	const std::lock_guard<std::mutex> lock(m_mutex);

	//std::cout << "Jumping" << std::endl;

	m_hasJumped = true;

	float vectorSize = m_gravity.getForce() + m_jumpPower;
	m_yVelocity = { 0.f, -vectorSize * deltaTime };

	for (float i = vectorSize; i > 0; i -= vectorSize / 120.f)
	{

		m_yVelocity.y += vectorSize / 120.f * deltaTime;

		if (m_yVelocity.y > 0) {
			m_yVelocity = { 0.f, 0.f };
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	m_hasJumped = false;
}

sf::Vector2f& Player::getYVelocity()
{
	return m_yVelocity;
}
