#include "gravity.h"

Gravity::Gravity() {}

void Gravity::applyGravity(Entity* entity, float deltaTime) {

	sf::Vector2f velocity = { 0.f, m_force * deltaTime };
	if (!entity->isCollisionDetected(velocity)) entity->getShape().setPosition(entity->getShape().getPosition() + velocity);
}

float Gravity::getForce()
{
	return m_force;
}
