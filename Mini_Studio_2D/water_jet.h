#pragma once

#include <thread>

#include "entity.h"
#include "gravity.h"

class WaterDroplet;

class WaterJet : public Entity {
public:
	WaterJet(int s, int h, Map& map, Entity* owner);
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	void newDroplet(float deltaTime);

private:
	Entity* m_owner;
	sf::RectangleShape m_waterHitbox;

	std::vector<std::shared_ptr<WaterDroplet>> m_waterDroplets;

	bool m_isActive = false;
};

class WaterDroplet : public Entity
{
public:
	WaterDroplet(Map& map);
	~WaterDroplet();

	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;

	void setRadius(float radius);
	void setDirection(sf::Vector2f newDirection);

	void checkIfOnStain();

	void decreseDirection(float deltaTime); //thread

public:
	sf::CircleShape shape;
	sf::Vector2f direction;

	float gravityMultiplier = .1f; //the gravity will smoothly affect the droplet

	Entity* owner;

	Gravity gravity;
};

