#include "game.h"
#include "menu_manager.h"

Game::Game() {}

void Game::run() {
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Mini Studio 2D");
	window.setFramerateLimit(120);

	Menu menu(1920, 1080);
	MenuManager menuManager(window, menu);

	Map map;

	map.createMap();

	EntityManager manager(map);

	sf::Clock clock;
	float deltaTime = 0.0f;

	while (window.isOpen()) {
		window.clear();

		deltaTime = clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		manager.CollideCheck(map, deltaTime);
		manager.player->update(deltaTime);
		

		menu.drawMenu(window);
		menuManager.handleEvents();

		window.clear();
		map.displayMap(window);
		manager.player->draw(window);
		window.display();
	}
}



