#include "game.h"

Game::Game() {}

void Game::run() {
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Mini Studio 2D");
	window.setFramerateLimit(60);

	Map map;
	Lamp lamp(64, 64);
	map.createMap();

	EntityManager manager;

	sf::Clock clock;
	float deltaTime = 0.0f;

	while (window.isOpen()) {

		deltaTime = clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		manager.player->update(deltaTime);
		manager.CollideCheck(map, deltaTime);
		lamp.update(deltaTime);

		window.clear();
		map.displayMap(window);
		manager.player->draw(window);
		lamp.draw(window);
		window.display();
	}
}
