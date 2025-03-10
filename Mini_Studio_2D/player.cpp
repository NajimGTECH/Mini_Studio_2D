#include "player.h"


Player::Player(int s, int h) : Entity(s, h)
{

}

void Player::update(float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		m_shape.move(2, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
		m_shape.move(0, -2);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		m_shape.move(0, 2);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
		m_shape.move(-2, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
		if (!m_hasJumped)

		std::thread(&Player::jump, this, deltaTime).detach();
	}

	m_gravity.applyGravity(this, deltaTime);
	m_shape.setPosition(m_shape.getPosition() + m_YVelocity);
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
}

void Player::jump(float deltaTime) 
{
	const std::lock_guard<std::mutex> lock(m_mutex);

	std::cout << "Jumping" << std::endl;

	m_hasJumped = true;

	m_YVelocity = { 0.f, 30.f * deltaTime };

	for (float i = 30.f; i > 0; i -= 1.f)
	{
		m_YVelocity -= { 0.f, 1.f * deltaTime };
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	m_hasJumped = false;
}