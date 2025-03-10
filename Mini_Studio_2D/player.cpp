#include "player.h"

Player::Player(int s, int h) : Entity(s, h)
{

}

void Player::update()
{

}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}