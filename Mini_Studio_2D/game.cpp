#include "game.h"
#include "menu_manager.h"

Game::Game() {}

void Game::run() {
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Mini Studio 2D");
	window.setFramerateLimit(120);

	Menu menu(1920, 1080);
	MenuManager menuManager(window, menu);

	Map map;

	EntityManager manager(map);

	sf::Clock clock;
	float deltaTime = 0.0f;

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
		}

		m_terminal = manager.TerminalCheck(map);


		manager.ButtonCheck(map, deltaTime);
		manager.player->update(deltaTime);
		

		menu.drawMenu(window);
		menuManager.handleEvents();

		window.clear();
		map.displayMap(window);
		manager.player->draw(window);
		window.display();
	}
}



