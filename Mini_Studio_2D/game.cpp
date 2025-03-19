#include "game.h"
#include "menu_manager.h"

Game::Game() {}

void Game::run() {
	m_terminal = false;
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Mini Studio 2D");
	window.setFramerateLimit(120);

	Menu menu(1920, 1080);
	MenuManager menuManager(window, menu);

	Map map;
	EntityManager manager(map);

	Closet closet(60, 60, map);
	Desk desk(60, 60, map);
	Box box(60, 60, map);
	BookShelf bookShelf(60, 60, map);
	Chair chair(60, 60, map);
	Shelf shelf(60, 60, map);

	sf::Clock clock;
	float deltaTime = 0.0f;

	bool menub = true;
	bool isPlaying = false;


	while (window.isOpen()) {
		window.clear();

		if (!map.loaded) {
			map.createMap(map.lvl);
			map.loaded = true;
			std::cout << "map loaded" << std::endl;
		}

		if (manager.player->getShape().getPosition().x > 1920) {
			map.lvl++;
			map.loaded = false;
			manager.player->getShape().setPosition(100, 500);
		}

		deltaTime = clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::E) {
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


		manager.player->update(deltaTime);
		if (menuManager.isPlayButtonClicked()) {
			isPlaying = true;
			menub = false;
		}


		if (isPlaying) {

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

		window.clear();
		map.displayMap(window);
		manager.player->draw(window);
		/*closet.draw(window);
		desk.draw(window);*/
		/*box.draw(window);*/
		/*bookShelf.draw(window);*/
		/*chair.draw(window);*/
		/*shelf.draw(window);*/

		window.display();
	}
}



