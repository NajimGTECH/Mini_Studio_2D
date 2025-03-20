#include"screen.h"

Screen::Screen(Map& map) {
	player = std::make_shared<Player>(sf::Vector2f(100, 170), 10, map);
	mainClock = std::make_shared<MainClock>(10);

	m_screenFont.loadFromFile("Assets/TextMenu/SolarPunk.otf");
	m_victory.setFont(m_screenFont);
	m_victory.setString("VICTORY");
	m_victory.setCharacterSize(100);
	m_victory.setPosition({ 750,400 });
	m_victory.setFillColor(sf::Color::Green);

	m_lose.setFont(m_screenFont);
	m_lose.setString("YOU LOSE !");
	m_lose.setCharacterSize(100);
	m_lose.setPosition({ 700,400 });
	m_lose.setFillColor(sf::Color::Red);

	backOpacity.setSize({1920,1080});
	backOpacity.setFillColor(sf::Color(255, 255, 255, 100));
}

void Screen::draw(sf::RenderWindow& window) {
	std::cout << mainClock->getIsAlive() << std::endl;
	if (!mainClock->getIsAlive()){
		window.draw(m_lose);     /////////////////////////////////////////// A VOIR POUR CLOCK DE TEMPS DE JEU //////////////////////////////////////////////////
		window.draw(backOpacity);
	}
	/*else* if(player->getEnd()){
		window.draw(m_victory);
		window.draw(backOpacity);
	}*/
}