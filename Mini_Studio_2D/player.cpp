#include "player.h"
#include <thread>
#include <iostream>

Player::Player(int s, int h) : Entity(s, h)
{

}

void Player::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		shape.move(2, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
		shape.move(0, -2);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		shape.move(0, 2);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
		shape.move(-2, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
		if (!jumped)
		jump();
	}

	gravity.applyGravity(this, 0.1f);
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

void Player::jump() {

}