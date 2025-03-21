#include "robotic_arm.h"

RoboticArm::RoboticArm(sf::Vector2f size, int health, Map& map, Entity* owner) : Entity(size, health, map)
{
	m_owner = owner;
	m_hand.setSize(m_owner->getShape().getSize() / 4.f);
	m_hand.setPosition(m_owner->getShape().getPosition() + (m_owner->getShape().getSize() / 4.f));
	
	if (!m_texture.loadFromFile("Assets/PLayer/ARM.png")) return;

	m_hand.setTexture(&m_texture);
}


void RoboticArm::update(float deltaTime)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && )
	{
		if(m_owner->getDirection().x == 1)
			m_hand.setPosition(m_owner->getShape().getPosition() + (m_owner->getShape().getSize() / 4.f) + (m_owner->getDirection() * 50.f));
			m_owner->isArmEquipped = true;
			m_isActive = true;
	}
	else
	{
		m_hand.setPosition(m_owner->getShape().getPosition() + (m_owner->getShape().getSize() / 4.f));
		m_owner->isArmEquipped = false;
		m_isActive = false;
	}
}

void RoboticArm::draw(sf::RenderWindow& window)
{
	// Draw the robotic arm
	if (m_isActive)
		window.draw(m_hand);
}

void RoboticArm::move()
{
	// Move the robotic arm
}

void RoboticArm::anim(float deltaTime)
{
}