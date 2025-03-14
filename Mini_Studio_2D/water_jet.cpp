#include "water_jet.h"

//* WATER JET *\\

WaterJet::WaterJet(int size, int health, Map& map, Entity* owner) : Entity(size, health, map)
{
		m_owner = owner;
		m_waterHitbox.setFillColor(sf::Color(0, 255, 255, 100));
		m_waterHitbox.setSize({ m_owner->getShape().getSize().x, m_owner->getShape().getSize().y / 1.5f });
}

void WaterJet::update(float deltaTime) 
{
		// Update the position of the water jet

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		std::cout << "Water jet used:\t" << m_owner->getDirection().x << ", " << m_owner->getDirection().y << std::endl;
		m_waterHitbox.setPosition(
			{
				m_owner->getShape().getPosition().x + (m_owner->getShape().getSize().x * m_owner->getDirection().x),
				m_owner->getShape().getPosition().y + ((m_owner->getShape().getSize().y / 4.75f) + (m_owner->getShape().getSize().y * m_owner->getDirection().y))
			}
		);
		m_isActive = true;
	}
	else
	{
		m_isActive = false;
	}
}

void WaterJet::draw(sf::RenderWindow & window) {
	// Draw the water jet
	if(m_isActive)
	window.draw(m_waterHitbox);
}

void WaterJet::move() {
	// Move the water jet
}

void WaterJet::waterAnimation(sf::RenderWindow& window)
{
	WaterDroplet newDrop(m_map);
	newDrop.setRadius(m_shape.getSize().y / 4.f);


}

//* WATER DROPLETS *\\

WaterDroplet::WaterDroplet(Map& map): Entity(10, -1, map)
{
}

void WaterDroplet::update(float deltaTime)
{
}

void WaterDroplet::draw(sf::RenderWindow& window)
{
}

void WaterDroplet::setRadius(float radius)
{
	shape.setRadius(radius);
}
