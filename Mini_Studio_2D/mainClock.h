#pragma once
#include <SFML/Graphics.hpp>

class MainClock
{
public:
	MainClock();
	MainClock(float timeInSeconds);

	void updateClock(sf::RenderWindow& window, float deltaTime);

	float getTime();
	bool getIsAlive();

private:

	void loadFont();

private:

	float m_time;
	sf::Font m_font;
	sf::Text m_text;

	bool m_isAlive = true;
};

