#include "robotic_arm.h"

RoboticArm::RoboticArm(int s, int h) : Entity(s, h) {
	/*texture.loadFromFile("assets/robotic_arm.png");
	sprite.setTexture(texture);*/
}

void RoboticArm::update(float deltaTime) {
	// Update the position of the robotic arm
}

void RoboticArm::draw(sf::RenderWindow& window) {
	window.draw(m_shape);
}

void RoboticArm::move() {
	// Move the robotic arm
}