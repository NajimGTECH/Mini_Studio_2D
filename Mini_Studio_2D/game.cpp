#include "game.h"

Game::Game() {}

void Game::run() {
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Mini Studio 2D");
	window.setFramerateLimit(60);

	Map map;

	EntityManager manager;

	sf::Clock clock;
	float deltaTime = 0.0f;

	while (window.isOpen()) {

		if (!map.loaded) {
			map.createMap(map.lvl);
			map.loaded = true;
			std::cout << "map loaded" << std::endl;
		}

		deltaTime = clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		manager.player->update(deltaTime);
		manager.CollideCheck(map, deltaTime);

		window.clear();
		map.displayMap(window);
		manager.player->draw(window);
		window.display();
	}
}
