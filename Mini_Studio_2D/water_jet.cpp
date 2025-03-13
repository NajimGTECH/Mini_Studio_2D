#include "water_jet.h"

WaterJet::WaterJet(int size, int health, Map& map) : Entity(size, health, map) {
	/*texture.loadFromFile("assets/water_jet.png");
	sprite.setTexture(texture);*/
}

void WaterJet::update(float deltaTime) {
	// Update the position of the water jet

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		std::cout << "Water jet used\n";
	}
}

void WaterJet::draw(sf::RenderWindow& window) {
	// Draw the water jet
}

void WaterJet::move() {
	// Move the water jet
}