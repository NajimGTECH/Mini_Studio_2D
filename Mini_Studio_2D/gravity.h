#pragma once
#include <SFML/System/Vector2.hpp>
#include "entity.h"

class Gravity
{
public:
	Gravity();

	void applyGravity(Entity* entity, float deltaTime);

	float getForce();

private : 
	float m_force = 9.81f*50; //9.81f
};
