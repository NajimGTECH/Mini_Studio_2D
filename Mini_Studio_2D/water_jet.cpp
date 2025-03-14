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
		//std::cout << "Water jet used:\t" << m_owner->getDirection().x << ", " << m_owner->getDirection().y << std::endl;
		m_waterHitbox.setPosition(
			{
				m_owner->getShape().getPosition().x + (m_owner->getShape().getSize().x * m_owner->getDirection().x),
				m_owner->getShape().getPosition().y + ((m_owner->getShape().getSize().y / 4.75f) + (m_owner->getShape().getSize().y * m_owner->getDirection().y))
			}
		);
		m_isActive = true;
		newDroplet(deltaTime);
	}
	else
	{
		m_isActive = false;
	}

	for (int i = m_waterDroplets.size() - 1; i >= 0; i--) {
		auto drop = m_waterDroplets[i];
		//std::cout << "POS: " << drop->getShape().getPosition().x << ", " << drop->getShape().getPosition().y << std::endl;
		if (drop->getShape().getPosition().y >= 2000) {
			drop.reset();
			m_waterDroplets.erase(m_waterDroplets.begin() + i);
		}
		else {
			drop->update(deltaTime);
		}
	}

	std::cout << m_waterDroplets.size() << std::endl;
}

void WaterJet::draw(sf::RenderWindow & window) {
	// Draw the water jet
	if(m_isActive)
	window.draw(m_waterHitbox);

	for (auto& drop : m_waterDroplets)
	{
		drop->draw(window);
	}
}

void WaterJet::newDroplet(float deltaTime)
{
	static float cooldownMax = .05f;
	static float cooldown = cooldownMax;

	//std::cout << "new droplet\n";

	if (cooldown >= cooldownMax)
	{
		auto newDrop = std::make_shared<WaterDroplet>(m_map);
		newDrop->setRadius(10.f); //m_shape.getSize().y / 4.f
		newDrop->setDirection(
			{
				m_owner->getDirection().x * 750,
				m_owner->getDirection().y * 750,
			}
			);
		newDrop->owner = m_owner;
		newDrop->shape.setPosition(newDrop->owner->getShape().getPosition() + newDrop->owner->getShape().getSize() / 2.f);

		std::thread(&WaterDroplet::decreseDirection, this, deltaTime).detach();

		m_waterDroplets.push_back(newDrop);

		cooldown = 0.f;
	}

	cooldown += deltaTime;
}

//* WATER DROPLETS *\\

WaterDroplet::WaterDroplet(Map& map): Entity(10, -1, map)
{
	shape.setFillColor(sf::Color(0, 255, 255, 255));
	shape.setRadius(10);
	owner = nullptr;
}

WaterDroplet::~WaterDroplet()
{
	//std::cout << "OOF\n";
}

void WaterDroplet::update(float deltaTime)
{
	sf::Vector2f moveVelocity = { deltaTime * direction.x, deltaTime * direction.y };

	//sf::Vector2f gravityVelocity = { 0.f, gravity.getForce()/2.f * deltaTime };

	shape.setPosition(shape.getPosition() + moveVelocity);
}

void WaterDroplet::draw(sf::RenderWindow& window)
{
	//std::cout << "draw\n";
	window.draw(shape);
}

void WaterDroplet::setRadius(float radius)
{
	shape.setRadius(radius);
}

void WaterDroplet::setDirection(sf::Vector2f newDirection)
{
	direction = newDirection;
}

void WaterDroplet::decreseDirection(float deltaTime)
{
	for (float i = vectorSize; i > 0; i -= vectorSize / 120.f)
	{
		jumpVelocity = { 0.f, vectorSize / 120.f * deltaTime };

		if (m_yVelocity.y > 0) {
			m_yVelocity = { 0.f, 0.f };
			break;
		}

		if (!isCollisionDetected(jumpVelocity)) { m_yVelocity += jumpVelocity; }
		else { m_yVelocity = { 0.f, 0.f }; std::cout << "Collision detected while jumping" << std::endl; break; }

		if (m_yVelocity.y == m_gravity.getForce() * deltaTime) break;

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}
