#include "game.h"
#include "menu_manager.h"

Game::Game() {}

void Game::run() {
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Mini Studio 2D");
	window.setFramerateLimit(60);

	Menu menu(1920, 1080);
	MenuManager menuManager(window, menu);

	Map map;

	map.createMap();

	EntityManager manager;

	sf::Clock clock;
	float deltaTime = 0.0f;

	bool isPlaying = false;


	while (window.isOpen()) {
		window.clear();

		deltaTime = clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		if (menuManager.isPlayButtonClicked()) {
			isPlaying = true;
		}

		if (isPlaying) {
			manager.player->update(deltaTime);
			manager.CollideCheck(map, deltaTime);

			map.displayMap(window);
			manager.player->draw(window);
		}
		else {
			menu.drawMenu(window);
			menuManager.handleEvents();
		}

		window.display();
	}
}



