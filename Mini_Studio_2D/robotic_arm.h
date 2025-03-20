#pragma once
#include "entity.h"

class RoboticArm : public Entity {
public:
	RoboticArm(sf::Vector2f size, int health, Map& map, Entity* owner);

	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	void move();
	void anim(float deltaTime) override;

private:

	Entity* m_owner;

	sf::RectangleShape m_hand;

	bool m_isActive = false;
	//float m_massAdded = 100.f;
};