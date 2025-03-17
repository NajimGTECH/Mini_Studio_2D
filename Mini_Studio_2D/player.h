#pragma once

#include <iostream>
#include <thread>
#include <mutex>

#include "entity.h"
#include "gravity.h"
#include "tools_include.h"

class Player : public Entity
{
public:
	Player(int size, int health, Map& map);

	int direction = 0;

	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	void anim(float deltatime) override;

	void jump(float deltaTime);

	sf::Vector2f getYVelocity();
	float getSpeed();
	bool isJumping();

	bool isMoving();

	void setYVelocity(sf::Vector2f newVelocity);
	void canJump(bool canJump);

private:

	bool checkIfGrounded();

private:

	sf::Vector2f m_yVelocity = { 0.f, 0.f };

	float m_jumpPower = 900.f;
	sf::Vector2i m_animVect = sf::Vector2i(0, 0);

	float m_speed = 500.f;
	sf::Clock m_animC;
	bool m_canJump = false;

	std::vector<std::shared_ptr<Entity>> m_tools;
;
	Gravity m_gravity;
	std::mutex m_mutex; //used to make player threads safe
};

