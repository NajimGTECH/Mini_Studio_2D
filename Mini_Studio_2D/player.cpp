#include "player.h"


Player::Player(int s, int h) : Entity(s, h)
{

}

void Player::update(float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		m_shape.move(2 * deltaTime * m_speed, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
		m_shape.move(0, -2 * deltaTime * m_speed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		m_shape.move(0, 2 * deltaTime * m_speed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
		m_shape.move(-2 * deltaTime * m_speed, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {

		if (!m_hasJumped)
		std::thread(&Player::jump, this, deltaTime).detach();
	}

	m_gravity.applyGravity(this, deltaTime);
	m_shape.setPosition(m_shape.getPosition() + m_yVelocity);
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