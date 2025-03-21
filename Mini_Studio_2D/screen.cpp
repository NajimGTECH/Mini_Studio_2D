#include"screen.h"

Screen::Screen(Map& map) {

	m_screenFont.loadFromFile("Assets/TextMenu/SolarPunk.otf");
	m_victory.setFont(m_screenFont);
	m_victory.setString("VICTORY");
	m_victory.setCharacterSize(200);
	m_victory.setPosition({ 600,400 });
	m_victory.setFillColor(sf::Color(0,128,0));

	/*m_lose.setFont(m_screenFont);
	m_lose.setString("YOU LOSE !");
	m_lose.setCharacterSize(200);
	m_lose.setPosition({ 500,400 });
	m_lose.setFillColor(sf::Color::Red);*/

	backOpacity.setSize({1920,1080});
	backOpacity.setFillColor(sf::Color(255, 255, 255, 180));
}

void Screen::plusCountLevel() {
	m_countLevel++;
	std::cout << m_countLevel;
}

int Screen::getCountLevel() {
	return m_countLevel;
}

void Screen::draw(sf::RenderWindow& window) {
	//if (mainClock->getIsAlive() == 0){
	//	window.draw(backOpacity);
	//	window.draw(m_lose);    /////////////////////////////////////////// A VOIR POUR CLOCK DE TEMPS DE JEU /////////////////////////////////////////////////
	//}
	if(m_countLevel == 10){
		window.draw(backOpacity);
		window.draw(m_victory);
	}
}