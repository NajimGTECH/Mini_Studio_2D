#include "mainClock.h"
#include<iostream>;
#include <chrono>

MainClock::MainClock()
{
	m_time = 10;
	m_text.setPosition({ 0, 0 });

	loadFont();
}

MainClock::MainClock(float timeInSeconds)
{
	m_time = timeInSeconds;
	m_text.setPosition({ 60, 50 });

	loadFont();
}

void MainClock::updateClock(sf::RenderWindow& window, float deltaTime)
{
	m_time -= deltaTime;

	if (m_time <= 0) {
		m_time = 0;
		m_isAlive = 0;
	}

	m_text.setString("Remaining time : " + std::to_string((int)m_time) + "s");
	window.draw(m_text);
}

void MainClock::loadFont()
{
	//not working on debug
	m_font.loadFromFile("Assets/TextMenu/SolarPunk.otf");
	m_text.setCharacterSize(50);
	m_text.setFillColor(sf::Color::Red);
	m_text.setFont(m_font);
}

float MainClock::getTime() { return m_time; }

int MainClock::getIsAlive() { return m_isAlive; }