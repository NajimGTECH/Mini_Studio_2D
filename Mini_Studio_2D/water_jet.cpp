#include "water_jet.h"

//* WATER JET *\\

WaterJet::WaterJet(sf::Vector2f size, int health, Map& map, Entity* owner) : Entity(size, health, map)
{
		m_owner = owner;
}

void WaterJet::update(float deltaTime)
{
	
	bool joystickMoved = sf::Joystick::getAxisPosition(0, sf::Joystick::U) > 50 || sf::Joystick::getAxisPosition(0, sf::Joystick::U) < -50 ||
		sf::Joystick::getAxisPosition(0, sf::Joystick::V) > 50 || sf::Joystick::getAxisPosition(0, sf::Joystick::V) < -50;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || joystickMoved)
	{
		sf::Vector2f playerPosition = m_owner->getShape().getPosition() + m_owner->getShape().getSize() / 2.f;
		sf::Vector2f direction;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			
			sf::Vector2i mousePosition = sf::Mouse::getPosition();
			direction = getDirectionFromPlayerToMouse(playerPosition, mousePosition);
		}
		else
		{
			float joystickU = sf::Joystick::getAxisPosition(0, sf::Joystick::U);
			float joystickV = sf::Joystick::getAxisPosition(0, sf::Joystick::V);

			direction = sf::Vector2f(joystickU, joystickV);
			float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
			if (length != 0)
			{
				direction /= length;
			}
		}


		m_direction = direction;
		m_isActive = true;
		newDroplet(deltaTime);
	}
	else
	{
		m_isActive = false;
	}

	for (int i = m_waterDroplets.size() - 1; i >= 0; i--) {
		auto drop = m_waterDroplets[i];
		if (drop->getShape().getPosition().y >= 2000 || drop->isCollisionDetected()) {
			drop.reset();
			m_waterDroplets.erase(m_waterDroplets.begin() + i);
		}
		else {
			drop->update(deltaTime);
		}
	}
}


void WaterJet::draw(sf::RenderWindow & window) {
	// Draw the water jet

	for (auto& drop : m_waterDroplets)
	{
		drop->draw(window);
	}
}

sf::Vector2f WaterJet::getDirectionFromPlayerToMouse(const sf::Vector2f& playerPosition, const sf::Vector2i& mousePosition)
{
	sf::Vector2f direction = sf::Vector2f(mousePosition.x, mousePosition.y) - playerPosition;

	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	if (length != 0)
	{
		direction /= length;
	}

	return direction;
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
				m_direction.x * 1100,
				m_direction.y * 1100,
			}
			);
		newDrop->owner = m_owner;
		newDrop->shape.setPosition(newDrop->owner->getShape().getPosition() + newDrop->owner->getShape().getSize() / 2.f);

		std::thread(&WaterDroplet::decreseDirection, newDrop, deltaTime).detach();

		m_waterDroplets.push_back(newDrop);

		cooldown = 0.f;
	}

	cooldown += deltaTime;
}

//* WATER DROPLETS *\\

WaterDroplet::WaterDroplet(Map& map): Entity(sf::Vector2f(10,10), -1, map)
{
	shape.setFillColor(sf::Color(0, 255, 255, 255));
	shape.setRadius(3);
	owner = nullptr;
}

WaterDroplet::~WaterDroplet()
{
	//std::cout << "OOF\n";
}

void WaterDroplet::update(float deltaTime)
{
	sf::Vector2f moveVelocity = { deltaTime * direction.x, deltaTime * direction.y };
	sf::Vector2f gravityVelocity = { 0.f, (gravity.getForce() * gravityMultiplier) * deltaTime };

	sf::Vector2f velocity = moveVelocity + gravityVelocity;

	shape.setPosition(shape.getPosition() + velocity);

	checkIfOnStain();
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

void WaterDroplet::checkIfOnStain()
{
	for (auto& stain : m_map.getAllStains()) {

		if (shape.getGlobalBounds().intersects(stain->shape.getGlobalBounds()))
		{
			stain->washStain();
		}
	}
}

void WaterDroplet::decreseDirection(float deltaTime)
{
	int maxLoop = 100;
	int loop = 0;

	while (loop <= maxLoop)
	{
		if (direction.x > 0)
		{
			direction.x -= 10.f;
		}
		else 
		if (direction.x < 0)
		{
			direction.x += 10.f;
		}

		if (direction.y > 0)
		{
			direction.y -= 10.f;
		}
		else
		if (direction.y < 0)
		{
			direction.y += 10.f;
		}

		shape.setFillColor(sf::Color(0, 255, 255, 255 - loop * 1.75f ));
		gravityMultiplier += .01f;
		loop++;

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	gravityMultiplier += 0.5f;
}

bool WaterDroplet::isCollisionDetected()
{
	for (auto& wall : m_map.getAllWalls()) {

		if (shape.getGlobalBounds().intersects(wall->shape.getGlobalBounds()))
		{
			return true;
		}
	}
	for (auto& door : m_map.getAllDoors()) {

		if (shape.getGlobalBounds().intersects(door->shape.getGlobalBounds()))
		{
			return true;
		}
	}
	return false;
}

void WaterJet::anim(float deltaTime)
{
}

void WaterDroplet::anim(float deltaTime) {

}