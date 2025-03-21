#pragma once

#include <thread>

#include "entity.h"
#include "gravity.h"

class WaterDroplet;

class WaterJet : public Entity {
public:
	WaterJet(sf::Vector2f s, int h, Map& map, Entity* owner);
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	void newDroplet(float deltaTime);
	void anim(float deltaTime) override;
	bool isMoving();
private:

	sf::Vector2f getDirectionFromPlayerToMouse(const sf::Vector2f& playerPosition, const sf::Vector2i& mousePosition);

private:
	Entity* m_owner;



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

	bool isCollisionDetected(); //checks if shape touches the walls

	void anim(float deltaTime) override;

	bool isMoving();

public:

	int m_diff;
	sf::CircleShape shape;
	sf::Vector2f direction;

	float gravityMultiplier = .1f; //the gravity will smoothly affect the droplet

	Entity* owner;

	Gravity gravity;
};

