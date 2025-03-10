#include "game.h"

Game::Game() {}

void Game::run() {
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Mini Studio 2D");
	window.setFramerateLimit(60);

	Player player(100, 10);

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
		player.update(deltaTime);

		window.clear();
		player.draw(window);
		window.display();
	}
}
