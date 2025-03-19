#pragma once

#include <memory>
#include <vector> // Include vector header

#include "backpack.h"
#include "enemy.h"
#include "player.h"
#include "map.h"
#include "digit.h"

class EntityManager
{
private:
	std::vector<std::unique_ptr<Digit>> m_buttons;
	sf::Font m_font;
	std::ifstream m_mapFile;
public:
	sf::Text code;
	std::shared_ptr<Player> player;
	std::shared_ptr<Backpack> backpack;
	std::vector<std::shared_ptr<Enemy>> enemies;

	EntityManager(Map& map);

	void generate(Map& map, int levelIndex);

	void ButtonCheck(Map& map, float deltaTime);
	bool TerminalCheck(Map& map);

	void deathCheck(Map& map);

	void displayTerminal(sf::RenderWindow& window, Map&);

};
