#include "game.h"
#include "menu_manager.h"

Game::Game() {}

void Game::run() {
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Mini Studio 2D");
	window.setFramerateLimit(120);

	Menu menu(1920, 1080);
	MenuManager menuManager(window, menu);

	Map map;
	Lamp lamp(60, 60, map);

	EntityManager manager(map);
	Closet closet(60, 60, map);
	Desk desk(60, 60, map);
	Box box(60, 60, map);
	BookShelf bookShelf(60, 60, map);
	Chair chair(60, 60, map);

	sf::Clock clock;
	float deltaTime = 0.0f;

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
		}

		manager.player->update(deltaTime);
		lamp.illuminate(map);
		lamp.raycast.attachedEntity = &lamp;
		if (menuManager.isPlayButtonClicked()) {
			isPlaying = true;
		}

		if (isPlaying) {
			manager.player->update(deltaTime);
			manager.ButtonCheck(map, deltaTime);
			map.displayMap(window);
			manager.player->draw(window);
		}
		else {
			menu.drawMenu(window);
			menuManager.handleEvents();
		}

		std::cout << deltaTime << endl;

		window.clear();
		map.displayMap(window);
		manager.player->draw(window);
		lamp.draw(window);
		/*closet.draw(window);
		desk.draw(window);*/
		/*box.draw(window);*/
		/*bookShelf.draw(window);*/
		chair.draw(window);
		window.display();
	}
}



