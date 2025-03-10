#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"

int main() {
	sf::RenderWindow window(sf::VideoMode({ 800.f, 600.f }), "Mini Studio 2D");

	Player player({ 100.f, 10.f });

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear();
		player.draw(window);
		window.display();
	}
}