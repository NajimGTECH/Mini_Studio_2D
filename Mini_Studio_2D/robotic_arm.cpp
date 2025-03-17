#include "robotic_arm.h"

RoboticArm::RoboticArm(int s, int h, Map& map) : Entity(s, h, map) 
{
	/*texture.loadFromFile("assets/robotic_arm.png");
	sprite.setTexture(texture);*/
}

void RoboticArm::update(float deltaTime) 
{
	// Update the position of the robotic arm
}

void RoboticArm::draw(sf::RenderWindow& window) 
{
	// Draw the robotic arm
}

void RoboticArm::move() 
{
	// Move the robotic arm
}