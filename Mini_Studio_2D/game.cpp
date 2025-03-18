#include "game.h"
#include "menu_manager.h"

Game::Game() {}

void Game::run() {
	m_terminal = false;
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Mini Studio 2D");
	window.setFramerateLimit(120);

	Map map;

	Menu menu(1920, 1080);
	MenuManager menuManager(window, menu, map);

	EntityManager manager(map);

	sf::Clock clock;
	float deltaTime = 0.0f;
	
	sf::Font font;
	if (!font.loadFromFile("Assets/TexteMenu/SolarPunk.otf")) {
		std::cerr << "Erreur : Impossible de charger la police SolarPunk.otf" << std::endl;
	}

	bool menub = true;
	bool isPlaying = false;


	while (window.isOpen()) {

		window.clear();

		if (manager.player->getShape().getPosition().x > 1950 || manager.player->getShape().getPosition().y > 1100)
		{
			map.currentLevel++;
			map.createMap(map.currentLevel);
			manager.generate(map, map.currentLevel);
			map.loaded = true;
			if (map.currentLevel == 1) {
				manager.player->getShape().setPosition(700, -100);
			}
			else
			manager.player->getShape().setPosition(100, 700);
		}

		deltaTime = clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::E) {
						if (manager.TerminalCheck(map)) {
						m_terminal = !m_terminal;
						manager.code.setString("");
					}
				}	
			}
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
			for (auto& npc : map.getAllNPCs()) {
				auto npcPtr = std::dynamic_pointer_cast<NPC>(npc);
				if (npcPtr && npcPtr->isNearPlayer(manager.player->getShape().getPosition().x,
					manager.player->getShape().getPosition().y)) {
					npcPtr->interact();
				}
			}
		}



		if (menuManager.isPlayButtonClicked()) {
			isPlaying = true;
			menub = false;
		}


		if (isPlaying) {
			
			manager.ButtonCheck(map, deltaTime);
			map.displayMap(window);
			manager.player->draw(window);
			for (auto enemy : manager.enemies) {
				enemy->draw(window);
				enemy->update(deltaTime);
			}
			if (map.currentLevel == 0) {
				if (manager.backpack) {
					manager.backpack->update(deltaTime);

					manager.backpack->draw(window);
					if (manager.player->getShape().getGlobalBounds().intersects(manager.backpack->getSprite().getGlobalBounds())) {
						manager.backpack.reset();
						manager.player->obtainBag();
					}
				}
			}
			if (!m_terminal) {
				manager.player->update(deltaTime);
			}
			else if (m_terminal) {
				manager.displayTerminal(window, map);
			}
		}
		else if (menub){
			menu.drawMenu(window);
			menuManager.handleEvents(deltaTime);
		}

		//std::cout << deltaTime << endl;
		window.display();
	}
}



