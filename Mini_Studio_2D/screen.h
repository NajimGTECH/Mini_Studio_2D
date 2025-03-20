#pragma once
#include"SFML/Graphics.hpp"

#include"player.h"

class Screen {
public:
	Screen();

	void draw(sf::RenderWindow& window);
	void update(float deltatime);

	Player* player;

private:
	sf::Text m_lose;
	sf::Text m_victory;
	sf::Font m_screenFont;
	sf::RectangleShape backOpacity;
};
