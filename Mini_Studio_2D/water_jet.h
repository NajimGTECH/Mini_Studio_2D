#pragma once
#include "entity.h"
#include "gravity.h"

class WaterJet : public Entity {
public:
	WaterJet(int s, int h, Map& map, Entity* owner);
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	void move();
	void waterAnimation(sf::RenderWindow& window);

private:
	Entity* m_owner;
	sf::RectangleShape m_waterHitbox;

	bool m_isActive = false;
};

class WaterDroplet : public Entity
{
public:
	WaterDroplet(Map& map);

	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;

	void setRadius(float radius);

public:
	sf::CircleShape shape;
	Gravity gravity;
};

