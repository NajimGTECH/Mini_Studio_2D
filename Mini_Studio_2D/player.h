#pragma once

#include <iostream>
#include <thread>
#include <mutex>

//#include "entity.h"
#include "gravity.h"
#include "tools_include.h"

class Player : public Entity
{
public:
	Player(sf::Vector2f size, int health, Map& map);

	int direction = 0;

	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	void anim(float deltatime) override;

	void jump(float deltaTime);

	void obtainBag();

	sf::Vector2f getYVelocity();
	float getSpeed();
	bool isJumping();
	bool getWalkSide() const;
	bool getE() const;
	void reverseE();

	bool isMoving();

	void setYVelocity(sf::Vector2f newVelocity);
	void canJump(bool canJump);

private:

	bool checkIfGrounded();

private:
	

	sf::Vector2f m_yVelocity = { 0.f, 0.f };

	float m_jumpPower = 900.f;



	bool m_canJump = false;
	bool m_walkSide = false;

	sf::Texture m_texturebis;

	std::vector<std::shared_ptr<Entity>> m_tools;

	Gravity m_gravity;
	std::mutex m_mutex; //used to make player threads safe
};

