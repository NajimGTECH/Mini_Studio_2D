#include "player.h"


Player::Player(sf::Vector2f size, int health, Map& map) : Entity(size, health, map)
{

	m_speed = 500.f;
	m_initialeSpeed = m_speed;

	m_scaling = 0.6;

	m_shape.setPosition(700, 300);
	m_base.setSize(sf::Vector2f(m_shape.getSize().x * 0.9f, m_shape.getSize().y / 10.f));

	m_base.setPosition(m_shape.getPosition().x + m_shape.getSize().x * 0.2f - m_shape.getSize().x / 7.f, m_shape.getPosition().y + m_shape.getSize().y*1.5 - m_base.getSize().y);


	m_inventory.addTool(std::make_shared<WaterJet>(sf::Vector2f(0, 0), -1, map, this));
	m_inventory.addTool(std::make_shared<RoboticArm>(sf::Vector2f(0, 0), -1, map, this));
	m_inventory.addTool(std::make_shared<Lamp>(sf::Vector2f(0, 0), -1, map, this));


	if (!m_texture.loadFromFile("Assets/Player/spritesheet_bag.png")) {
		return;
	}

	if (!m_texturebis.loadFromFile("Assets/Player/spritesheet_nobag.png")) {
		return;
	}

	if (m_hasBag) {
		m_coeffAnim = sf::Vector2f(214, 328);
		m_scaling = 0.4;
		
	}
	else {
		m_coeffAnim = sf::Vector2f(175, 356);
		m_scaling = 0.35;
		
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_shape.getPosition());
	m_sprite.setScale(m_scaling, m_scaling);
}

void Player::update(float deltaTime)
{
	m_speed = m_initialeSpeed;

	if (m_hasBag) {
		m_coeffAnim = sf::Vector2f(214, 328);
		m_scaling = 0.4;
		m_sprite.setTexture(m_texture);
	}
	else {
		m_coeffAnim = sf::Vector2f(175, 356);
		m_scaling = 0.35;
		m_sprite.setTexture(m_texturebis);
	}

	sf::Vector2f moveVelocity = { 0.f, 0.f };
	m_direction = { 0.f, 0.f };

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 30 || sf::Joystick::getAxisPosition(0, sf::Joystick::PovX) > 30)
	{
		m_walkSide = true;

		m_sprite.setOrigin(0, 0);
		m_sprite.setScale(m_scaling, m_scaling);

		moveVelocity = { deltaTime * m_speed, 0.f };
		m_direction += { 1.f, 0.f };

		auto pushedFurniture = checkIfFurnitureIsPushed(moveVelocity);

		if (pushedFurniture != nullptr && m_speed == m_initialeSpeed)
		{
			//std::cout << "furniture detected\n";

			if (isArmEquipped)
			{
				m_speed -= pushedFurniture->getMass()/2.f;
			}
			else
			{
				m_speed -= pushedFurniture->getMass();
			}

			moveVelocity = { deltaTime * m_speed, 0.f };
			
			if (!isCollisionDetectedBetweenFurnitureAndWalls(pushedFurniture))
			{
				pushedFurniture->shape.setPosition(pushedFurniture->shape.getPosition() + moveVelocity);
			}
			else
			{
				m_speed = 0;
				moveVelocity = { deltaTime * m_speed, 0.f };
			}

		}

		if (!isCollisionDetected(moveVelocity)) m_shape.setPosition(m_shape.getPosition() + moveVelocity);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -30 || sf::Joystick::getAxisPosition(0, sf::Joystick::PovX) < -30)
	{
		m_walkSide = false;

		m_sprite.setOrigin(175, 0);
		m_sprite.setScale(-m_scaling, m_scaling);

		moveVelocity = { deltaTime * -m_speed, 0.f }; 
		m_direction += { -1.f, 0.f };

		auto pushedFurniture = checkIfFurnitureIsPushed(moveVelocity);

		if (pushedFurniture != nullptr && m_speed == m_initialeSpeed)
		{
			//std::cout << "furniture detected\n";

			if (isArmEquipped)
			{
				m_speed -= pushedFurniture->getMass() / 2.f;
			}
			else
			{
				m_speed -= pushedFurniture->getMass();
			}

			moveVelocity = { deltaTime * -m_speed, 0.f };
			
			if (!isCollisionDetectedBetweenFurnitureAndWalls(pushedFurniture))
			{
				pushedFurniture->shape.setPosition(pushedFurniture->shape.getPosition() + moveVelocity);
			}
			else
			{
				m_speed = 0;
				moveVelocity = { deltaTime * -m_speed, 0.f };
			}
		}

		if(!isCollisionDetected(moveVelocity)) m_shape.setPosition(m_shape.getPosition() + moveVelocity);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
	{
		m_direction += { 0.f, -1.f };
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		m_direction += { 0.f, 1.f };
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) || sf::Joystick::isButtonPressed(0 , 0) || sf::Joystick::getAxisPosition(0, sf::Joystick::PovY) > 30) {

		if (m_canJump)
		std::thread(&Player::jump, this, deltaTime).detach();
	}

	m_shape.setPosition(m_shape.getPosition() + m_yVelocity);
	m_base.setPosition(m_shape.getPosition().x + m_shape.getSize().x * 0.2f - m_shape.getSize().x / 7.f, m_shape.getPosition().y + m_shape.getSize().y - m_base.getSize().y + 10);

	if (checkIfGrounded())
	{
		
		m_canJump = true;

		if (isCollisionDetected({0, 0}))
		{
			m_yVelocity.y = -m_gravity.getForce() * deltaTime; //to avoid getting stuck
		}
		else
		{
			m_yVelocity.y = 0.f;
		}
	}
	else
	{
		//std::cout << "midair:\t" << m_yVelocity.y << std::endl;
		m_gravity.applyGravity(this, deltaTime);
		m_canJump = false;
	}

	//std::cout << "Plr velocity: " << getYVelocity().x << ", " << getYVelocity().y << std::endl;

	//update loop for the player tools
	for (auto& tool : m_tools)
	{
		tool->update(deltaTime);
	}

	m_sprite.setPosition(m_shape.getPosition().x, m_shape.getPosition().y + 5);
	m_sprite.setTextureRect(sf::IntRect(m_animVect.x * m_coeffAnim.x, m_animVect.y * m_coeffAnim.y, m_coeffAnim.x, m_coeffAnim.y));
	anim(deltaTime);

	if (sf::Joystick::isButtonPressed(0, 4)) {
		m_inventory.switchTool(0);
	}
	if (sf::Joystick::isButtonPressed(0, 5)) {
		m_inventory.switchTool(1);
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
		m_inventory.switchTool(0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
		m_inventory.switchTool(1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
		m_inventory.switchTool(2);
	}
	m_inventory.update(deltaTime);

}

void Player::draw(sf::RenderWindow& window)
{
	//window.draw(m_shape);
	window.draw(m_sprite);
	m_base.setFillColor(sf::Color::Blue);
	//window.draw(m_base);
	m_inventory.draw(window);
	//draw loop for the player tools
	for (auto& tool : m_tools)
	{
		tool->draw(window);
	}
}

void Player::jump(float deltaTime) 
{
	const std::lock_guard<std::mutex> lock(m_mutex);

	if (m_canJump == false) return;


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
		else { m_yVelocity = { 0.f, 0.f };  break; }

		if (m_yVelocity.y == m_gravity.getForce() * deltaTime) break;

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
}

void Player::obtainBag()
{
	m_hasBag = true;
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

bool Player::getWalkSide() const {
	return m_walkSide;
}

bool Player::getE() const {
	return E;
}

void Player::reverseE() {
	E = !E;
}

bool Player::getEnd() {
	return end;
}

bool Player::isMoving()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 30 || sf::Joystick::getAxisPosition(0, sf::Joystick::PovX) > 30
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -30 || sf::Joystick::getAxisPosition(0, sf::Joystick::PovX) < -30;
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
	for (auto& furn : m_map.getAllFurnitures()) {

		if (m_base.getGlobalBounds().intersects(furn->shape.getGlobalBounds()))
		{
			return true;
		}
	}
	return false;
}

std::shared_ptr<MapElements> Player::checkIfFurnitureIsPushed(sf::Vector2f targetPosition)
{
	sf::RectangleShape dummyRec;
	dummyRec.setSize(m_shape.getSize());
	dummyRec.setPosition(m_shape.getPosition() + targetPosition);

	for (auto& furniture : m_map.getAllFurnitures()) {

		if (dummyRec.getGlobalBounds().intersects(furniture->shape.getGlobalBounds()))
		{
			//std::cout << "found furniture\n";

			return furniture;
		}
	}

	return nullptr;
}

bool Player::isCollisionDetectedBetweenFurnitureAndWalls(std::shared_ptr<MapElements> furniture)
{
	for (auto& wall : m_map.getAllWalls()) {

		if (furniture->shape.getGlobalBounds().intersects(wall->shape.getGlobalBounds()) && wall->canCollide)
		{
			return true;
		}
	}
	for (auto& door : m_map.getAllDoors()) {

		if (furniture->shape.getGlobalBounds().intersects(door->shape.getGlobalBounds()) && door->canCollide)
		{
			return true;
		}
	}
	return false;
}

void Player::anim(float deltaTime)
{
	int timeAnimation = m_animC.getElapsedTime().asMilliseconds();

	if (isMoving()) {
		if (timeAnimation >= 150) {
			m_animVect.x++;
			m_animC.restart();
		}
		if (m_animVect.x * m_coeffAnim.x >= m_texture.getSize().x) {
			m_animVect.x = 0;
			m_animVect.y += 1;
		}
		if (m_animVect.y * m_coeffAnim.y >= m_texture.getSize().y) {
			m_animVect.y = 0;
		}
	}
}