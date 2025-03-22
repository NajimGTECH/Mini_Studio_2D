#pragma once
#include <SFML/Graphics.hpp>

class MainClock
{
public:
	MainClock();
	MainClock(float timeInSeconds);

	void updateClock(sf::RenderWindow& window, float deltaTime);

	float getTime();
	int getIsAlive();

private:

	void loadFont();

private:

	float m_time;
	sf::Font m_font;
	sf::Text m_text;

	int m_isAlive = 1;
};

