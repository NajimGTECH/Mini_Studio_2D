#pragma once
#include <SFML/System/Vector2.hpp>
#include "entity.h"

class Gravity
{
private : 
	float force = 9.81f;
public:
	Gravity();
	void applyGravity(Entity* entity, float);
};
