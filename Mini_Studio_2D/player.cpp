#include "player.h"


Player::Player(int size, int health, Map& map) : Entity(size, health, map)
{
	m_shape.setPosition(500, 400);
	m_base.setSize(sf::Vector2f(m_shape.getSize().x * 0.9f, m_shape.getSize().y / 10.f));

	m_base.setPosition(m_shape.getPosition().x + m_shape.getSize().x * 0.2f - m_shape.getSize().x/7.f, m_shape.getPosition().y + m_shape.getSize().y - m_base.getSize().y);
}

void Player::update(float deltaTime)
{
	sf::Vector2f moveVelocity = { 0.f, 0.f };

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 30)
	{
		moveVelocity = { deltaTime * m_speed, 0.f };
		if (!isCollisionDetected(moveVelocity)) m_shape.setPosition(m_shape.getPosition() + moveVelocity);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -30)
	{
		moveVelocity = { deltaTime * -m_speed, 0.f };
		if(!isCollisionDetected(moveVelocity)) m_shape.setPosition(m_shape.getPosition() + moveVelocity);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) || sf::Joystick::isButtonPressed(0 , 0)) {

		if (m_canJump)
		std::thread(&Player::jump, this, deltaTime).detach();
	}

	m_shape.setPosition(m_shape.getPosition() + m_yVelocity);
	m_base.setPosition(m_shape.getPosition().x + m_shape.getSize().x * 0.2f - m_shape.getSize().x / 7.f, m_shape.getPosition().y + m_shape.getSize().y - m_base.getSize().y + 5);

	if (checkIfGrounded())
	{
		m_yVelocity.y = 0.f;
		//std::cout << "grounded:\t" << m_yVelocity.y << std::endl;
		m_canJump = true;
	}
	else
	{
		//std::cout << "midair:\t" << m_yVelocity.y << std::endl;
		m_gravity.applyGravity(this, deltaTime);
		m_canJump = false;
	}

	//std::cout << "Plr velocity: " << getYVelocity().x << ", " << getYVelocity().y << std::endl;
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
	m_base.setFillColor(sf::Color::Blue);
	window.draw(m_base);
}

void Player::jump(float deltaTime) 
{
	const std::lock_guard<std::mutex> lock(m_mutex);

	if (m_canJump == false) return;

	std::cout << "Jumping" << std::endl;

	m_canJump = false;

	float vectorSize = m_gravity.getForce() + m_jumpPower;
	m_yVelocity = { 0.f, -vectorSize * deltaTime };

	sf::Vector2f jumpVelocity;

	for (float i = vectorSize; i > 0; i -= vectorSize / 120.f)
	{
		jumpVelocity = { 0.f, vectorSize / 120.f * deltaTime };

		if (m_yVelocity.y > 0) {
			m_yVelocity = { 0.f, 0.f };
			break;
		}

		if (!isCollisionDetected(jumpVelocity)) { m_yVelocity += jumpVelocity;  }
		else { m_yVelocity = { 0.f, 0.f }; std::cout << "Collision detected while jumping" << std::endl; break; }

		if (m_yVelocity.y == m_gravity.getForce() * deltaTime) break;

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

sf::Vector2f Player::getYVelocity()
{
	return m_yVelocity;
}

float Player::getSpeed()
{
	return m_speed;
}

bool Player::isJumping()
{
	return m_canJump;
}

void Player::setYVelocity(sf::Vector2f newVelocity)
{
	m_yVelocity = newVelocity;
}

void Player::canJump(bool canJump)
{
	m_canJump = canJump;
}

bool Player::checkIfGrounded()
{
	for (auto& wall : m_map.getAllWalls()) {

		if (m_base.getGlobalBounds().intersects(wall->shape.getGlobalBounds()))
		{
			return true;
		}
	}
	return false;
}

