#pragma once

#include <iostream>
#include <thread>
#include <mutex>

#include "entity.h"
#include "gravity.h"

class Player : public Entity
{
public:
	
	Player(int s, int h);

	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;

	void jump(float deltaTime);

private:

	bool m_hasJumped = false;
	Gravity m_gravity;

	std::mutex m_mutex;

	sf::Vector2f m_YVelocity = { 0.f, 0.f };
};

