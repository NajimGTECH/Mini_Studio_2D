
#include"screen.h"

Screen::Screen() {
	m_screenFont.loadFromFile("Assets/TextMenu/SolarPunk.otf");
	m_victory.setFont(m_screenFont);
	m_victory.setString("VICTORY");
	m_victory.setCharacterSize(100);
	m_victory.setFillColor(sf::Color::Green);

	m_lose.setFont(m_screenFont);
	m_lose.setString("YOU LOSE !");
	m_lose.setCharacterSize(100);
	m_lose.setFillColor(sf::Color::Red);

	backOpacity.setSize({ 1920,1080 });
	backOpacity.setFillColor(sf::Color(255, 255, 255, 100));
}

void Screen::draw(sf::RenderWindow& window) {
	//if (!getIsAlive()){ // 
	//	window.draw(m_lose); /////////////////////////////////////////// A VOIR POUR CLOCK DE TEMPS DE JEU //////////////////////////////////////////////////////
	// window.draw(backOpacity);
	//}
	/*else*/ if(player->getEnd()){ // 
		window.draw(m_victory);
		window.draw(backOpacity);
	}
}

void Screen::update(float deltaTime) {
	//if (!getIsAlive()){ // 
	//	;
	//}
	/*else*/ if (player->getEnd()) { // 
		m_victory.setPosition({400, 400});
	}
}