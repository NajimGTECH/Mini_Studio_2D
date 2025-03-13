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
						if (manager.TerminalCheck(map)) {
						m_terminal = !m_terminal;
					}
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
			if (!m_terminal) {
				manager.player->update(deltaTime);
			}
			else if (m_terminal) {
				sf::RectangleShape darkback;
				darkback.setSize(sf::Vector2f(1920, 1080));
				darkback.setFillColor(sf::Color(0, 0, 0, 200));
				window.draw(darkback);
				sf::RectangleShape terminal;
				terminal.setSize(sf::Vector2f(800, 600));
				terminal.setPosition(560, 240);
				terminal.setFillColor(sf::Color(150, 150, 150));
				window.draw(terminal);
			}
		}
		else if (menub){
			menu.drawMenu(window);
			menuManager.handleEvents();
		}

		//std::cout << deltaTime << endl;
		window.display();
	}
}



