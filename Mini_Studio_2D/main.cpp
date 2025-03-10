#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Mini Studio 2D");

	Player player(100, 10);

	window.setFramerateLimit(60);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				std::cout << "Window closed" << std::endl;
			}
		}

		player.update();

		window.clear();
		player.draw(window);
		window.display();
	}
}