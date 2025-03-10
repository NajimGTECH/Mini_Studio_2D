#include "player.h"

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
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}