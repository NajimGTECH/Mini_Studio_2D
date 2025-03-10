#pragma once

#include <iostream>
#include <thread>
#include <mutex>

#include "entity.h"
#include "gravity.h"
#include "map.h"

class Player : public Entity
{
public:
	
	Player(int size, int health);

	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;

	void jump(float deltaTime);

private:

	sf::Vector2f m_yVelocity = { 0.f, 0.f };

	float m_jumpPower = 700.f;
	float m_speed = 250.f;

	bool m_hasJumped = false;
;
	Gravity m_gravity;

	std::mutex m_mutex;
};

