#include "water_jet.h"

//* WATER JET *\\

WaterJet::WaterJet(sf::Vector2f size, int health, Map& map, Entity* owner) : Entity(size, health, map)
{
		m_owner = owner;
		
		if (!m_texture.loadFromFile("Assets/Player/bah_pipe_water.png")) return;

		m_coeffAnim = (sf::Vector2f(195, 65));

		m_shape.setTexture(&m_texture);
		m_shape.setOrigin(-50 , 0);
		m_shape.setPosition(m_owner->getShape().getPosition());
		m_shape.setSize(sf::Vector2f(100, 100));
		m_shape.setFillColor(sf::Color::White);

		m_shape.setTextureRect(sf::IntRect(m_animVect.x * m_coeffAnim.x, m_animVect.y * m_coeffAnim.y, m_coeffAnim.x, m_coeffAnim.y));

}

void WaterJet::update(float deltaTime)
{
	
	bool joystickMoved = sf::Joystick::getAxisPosition(0, sf::Joystick::U) > 50 || sf::Joystick::getAxisPosition(0, sf::Joystick::U) < -50 ||
		sf::Joystick::getAxisPosition(0, sf::Joystick::V) > 50 || sf::Joystick::getAxisPosition(0, sf::Joystick::V) < -50;

	if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) || joystickMoved) && m_owner->hasBag())
	{
		sf::Vector2f playerPosition = m_owner->getShape().getPosition() + m_owner->getShape().getSize() / 2.f;
		sf::Vector2f direction;


		anim(deltaTime);


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

		static int diff = 0;



		if (m_owner->getDirection().x == 1) {
			m_shape.setOrigin(-50, 0);
			m_shape.setScale(1, 1);
			diff = 35;
		}

		if (m_owner->getDirection().x == -1) {
			m_shape.setOrigin(50, 0);
			m_shape.setScale(-1, 1);
			diff = -90;
		}

		m_shape.setPosition(m_owner->getShape().getPosition().x + diff, m_owner->getShape().getPosition().y + 40);

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
	
	
	if (m_isActive)
		window.draw(m_shape);


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

		static int diff = 0;
		
		if (newDrop->owner->getDirection().x == 1) {
			diff = 50;
		}

		if (newDrop->owner->getDirection().x == -1) {
			diff = -100;
		}
	
		newDrop->m_diff = diff;

		newDrop->shape.setPosition(newDrop->shape.getPosition().x + newDrop->m_diff, newDrop->shape.getPosition().y - 22);

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
	shape.setRadius(5);
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

		if (shape.getGlobalBounds().intersects(wall->shape.getGlobalBounds()) && wall->canCollide)
		{
			return true;
		}
	}
	for (auto& door : m_map.getAllDoors()) {

		if (shape.getGlobalBounds().intersects(door->shape.getGlobalBounds()) && door->canCollide)
		{
			return true;
		}
	}
	return false;
}

void WaterJet::anim(float deltaTime)
{
	int timeAnimation = m_animC.getElapsedTime().asMilliseconds();

	if (timeAnimation >= 50 && m_animVect.x < 14) {
		m_animVect.x++;
		m_animC.restart();
		std::cout << "anim";
	}
}

bool WaterJet::isMoving()
{
	return false;
}

void WaterDroplet::anim(float deltaTime) {

}

bool WaterDroplet::isMoving()
{
	return false;
}
