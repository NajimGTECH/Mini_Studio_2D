#include "water_jet.h"

//* WATER JET *\\

WaterJet::WaterJet(sf::Vector2f size, int health, Map& map, Entity* owner) : Entity(size, health, map)
{
		m_owner = owner;
		
		if (!m_texture.loadFromFile("Assets/Player/bag_pipe_water.png")) return;

		m_coeffAnim = (sf::Vector2f(195, 65));

		m_animVect = sf::Vector2f(0, 0);

		m_shape.setTexture(&m_texture);
		m_shape.setOrigin(-50 , 0);
		m_shape.setPosition(m_owner->getShape().getPosition());
		m_shape.setSize(sf::Vector2f(200, 100));
		m_shape.setFillColor(sf::Color::White);

		m_shape.setTextureRect(sf::IntRect(m_animVect.x * m_coeffAnim.x, m_animVect.y * m_coeffAnim.y, m_coeffAnim.x, m_coeffAnim.y));

}

void WaterJet::update(float deltaTime)
{
	bool joystickMoved = sf::Joystick::getAxisPosition(0, sf::Joystick::U) > 50 ||
		sf::Joystick::getAxisPosition(0, sf::Joystick::U) < -50 ||
		sf::Joystick::getAxisPosition(0, sf::Joystick::V) > 50 ||
		sf::Joystick::getAxisPosition(0, sf::Joystick::V) < -50;

	bool shouldBeActive = (sf::Mouse::isButtonPressed(sf::Mouse::Left) || joystickMoved) && m_owner->hasBag();

	if (shouldBeActive && m_animState == IDLE) {
		m_animState = APPEARING;
		m_animTime = 0.f;
	}

	if (!shouldBeActive && m_animState == ACTIVE) {
		m_animState = DISAPPEARING;
		m_animTime = 0.f;
	}

	anim(deltaTime);

	static int diff = 0;

	if (m_owner->getDirection().x == 1) {
		diff = -43;
		m_shape.setOrigin(-50, 0);
		m_shape.setScale(1, 1);
	}

	if (m_owner->getDirection().x == -1) {
		diff = -90;
		m_shape.setOrigin(147, 0);
		m_shape.setScale(-1, 1);
	}

	if (m_animState != IDLE) {
		m_shape.setPosition(m_owner->getShape().getPosition().x + diff, m_owner->getShape().getPosition().y + 10);
	}

	if (m_animState == ACTIVE) {
		sf::Vector2f playerPosition = m_owner->getShape().getPosition() + m_owner->getShape().getSize() / 2.f;
		sf::Vector2f direction;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2i mousePosition = sf::Mouse::getPosition();
			direction = getDirectionFromPlayerToMouse(playerPosition, mousePosition);
		}
		else {
			float joystickU = sf::Joystick::getAxisPosition(0, sf::Joystick::U);
			float joystickV = sf::Joystick::getAxisPosition(0, sf::Joystick::V);
			direction = sf::Vector2f(joystickU, joystickV);
			float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
			if (length != 0) direction /= length;
		}

		m_direction = direction;
		newDroplet(deltaTime);
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



void WaterJet::draw(sf::RenderWindow& window) {
	if (m_animState != IDLE) {
		window.draw(m_shape);
	}

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

		newDrop->shape.setPosition(newDrop->shape.getPosition().x + newDrop->m_diff, newDrop->shape.getPosition().y + 10);

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
	m_animTime += deltaTime;

	// Phase d'apparition
	if (m_animState == APPEARING) {
		// On garde le jet visible pendant l'animation d'apparition
		if (m_animTime >= m_animDuration) {
			m_animState = ACTIVE;  // L'animation d'apparition est terminée
			m_animVect.x = 14;     // On finit l'animation d'apparition
			std::cout << "Fin de l'animation d'apparition\n";
			m_shape.setFillColor(sf::Color(255, 255, 255, 255));  // Assurer que le jet est totalement visible
		}
		else {
			// Animation d'apparition : on part de 14 et on va vers 0
			m_animVect.x = 14 - static_cast<int>((m_animTime / m_animDuration) * 14);
			std::cout << "Animation d'apparition: Frame " << m_animVect.x << "\n";
			m_shape.setFillColor(sf::Color(255, 255, 255, 255));  // Garder la shape visible pendant l'animation
		}
	}

	// Phase d'activation (le jet est toujours visible)
	if (m_animState == ACTIVE) {
		m_shape.setFillColor(sf::Color(255, 255, 255, 255));  // Toujours visible
		m_animVect.x = 0;  // Utiliser la dernière frame de l'animation
	}

	// Phase de disparition
	if (m_animState == DISAPPEARING) {
		if (m_animTime >= m_animDuration) {
			m_animState = IDLE;  // L'animation de disparition est terminée
			m_animVect.x = 0;    // Le jet est totalement caché
			std::cout << "Fin de l'animation de disparition\n";
			m_shape.setFillColor(sf::Color(255, 255, 255, 0));  // Le jet devient transparent
		}
		else {
			// Animation de disparition : on part de 0 et on va vers 14
			m_animVect.x = static_cast<int>((m_animTime / m_animDuration) * 14);
			std::cout << "Animation de disparition: Frame " << m_animVect.x << "\n";
			// Pendant l'animation de disparition, on commence à rendre le jet plus transparent
			int alpha = static_cast<int>(255 - ((m_animTime / m_animDuration) * 255));
			m_shape.setFillColor(sf::Color(255, 255, 255, alpha));  // On réduit la transparence
		}
	}

	// Mise à jour de la texture du sprite
	m_shape.setTextureRect(sf::IntRect(m_animVect.x * m_coeffAnim.x, m_animVect.y * m_coeffAnim.y, m_coeffAnim.x, m_coeffAnim.y));
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
