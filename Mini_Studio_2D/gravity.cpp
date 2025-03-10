#include "gravity.h"

Gravity::Gravity() {}

void Gravity::applyGravity(Entity* entity, float deltaTime) {
	sf::Vector2f velocity = sf::Vector2f(0.f, force * deltaTime);
	entity->getShape().setPosition(entity->getShape().getPosition() + velocity);
}