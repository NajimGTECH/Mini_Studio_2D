#pragma once

#include <memory>
#include <vector> // Include vector header

#include "map.h"
#include "digit.h"
class Player;
class EntityManager
{
private:
	std::vector<std::unique_ptr<Digit>> m_buttons;
	sf::Font m_font;
public:
	sf::Text code;
	std::shared_ptr<Player> player;

	EntityManager(Map& map);

	void ButtonCheck(Map& map, float deltaTime);
	bool TerminalCheck(Map& map);

	void displayTerminal(sf::RenderWindow& window, Map&);

};
