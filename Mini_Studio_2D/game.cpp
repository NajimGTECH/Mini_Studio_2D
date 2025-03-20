#include "game.h"
#include "menu_manager.h"

Game::Game() {}

void Game::run() {
	m_terminal = false;
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Mini Studio 2D");
	window.setFramerateLimit(120);

	Map map;
	EntityManager manager(map);

	/*Closet closet(60, 60, map);
	Desk desk(60, 60, map);
	Box box(60, 60, map);
	BookShelf bookShelf(60, 60, map);
	Chair chair(60, 60, map);
	Shelf shelf(60, 60, map);*/
	Menu menu(1920, 1080);
	MenuManager menuManager(window, menu, map);
	MainClock mainClock(300);


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
		deltaTime = clock.restart().asSeconds();

		if (manager.player->getShape().getPosition().x > 1950) 
		{
			map.createMap(map.currentLevel + 1);
			map.loaded = true;
			manager.player->getShape().setPosition(100, 700);
		}

		

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::R) {
					manager.player->reverseE();
				}
			}
		}
		if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::E) {
				if (manager.TerminalCheck(map)) {
					m_terminal = !m_terminal;
					manager.code.setString("");
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

			mainClock.updateClock(window, deltaTime);
			manager.ButtonCheck(map, deltaTime);
			map.displayMap(window);
			manager.player->draw(window);
			if (!m_terminal) {
				manager.player->update(deltaTime);
			}
			else if (m_terminal) {
				manager.displayTerminal(window, map);
			}
		}
		else if (menub) {
			menu.drawMenu(window);
			menuManager.handleEvents(deltaTime);
		}

		
		map.displayMap(window);
		/*closet.draw(window);
		desk.draw(window);*/
		/*box.draw(window);*/
		/*bookShelf.draw(window);*/
		/*chair.draw(window);*/
		/*shelf.draw(window);*/

		window.display();
	}
}



