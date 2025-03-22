#pragma once
#include"SFML/Graphics.hpp"
#include"player.h"
#include"mainClock.h"
#include"map.h"

class Screen {
public:
	Screen(Map& map);

	void draw(sf::RenderWindow& window);
	void plusCountLevel();
	int getCountLevel();

	std::shared_ptr<Player>player;
	std::shared_ptr<MainClock>mainClock;

private:
	sf::Text m_lose;
	sf::Text m_victory;
	sf::Font m_screenFont;
	sf::RectangleShape backOpacity;

	int m_countLevel = 8;
};
