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

	manager.addNPC(sf::Vector2f(400, 500), map);


	sf::Clock clock;
	float deltaTime = 0.0f;
	
	sf::Font font;
	if (!font.loadFromFile("Assets/TexteMenu/SolarPunk.otf")) {
		std::cerr << "Erreur : Impossible de charger la police arial.ttf" << std::endl;
	}

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

		if (menuManager.isPlayButtonClicked()) {
			isPlaying = true;
		}

		if (isPlaying) {
			manager.player->update(deltaTime);
			manager.ButtonCheck(map, deltaTime);
			map.displayMap(window);
			manager.player->draw(window);
			manager.drawNPCs(window);

			for (auto& npc : manager.npcs) {
				if (npc->isPlayerNearby(manager.player->getShape().getPosition())) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
						sf::Text dialogue;
						dialogue.setFont(font);
						dialogue.setString(npc->getDialogue());
						dialogue.setCharacterSize(20);
						dialogue.setFillColor(sf::Color::White);
						dialogue.setPosition(npc->getShape().getPosition().x, npc->getShape().getPosition().y - 40);
						window.draw(dialogue);
					}
				}
			}
		}
		else {
			menu.drawMenu(window);
			menuManager.handleEvents();
		}

		std::cout << deltaTime << endl;

		window.display();
	}
}



