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
	
	sf::Font font;
	if (!font.loadFromFile("Assets/TexteMenu/SolarPunk.otf")) {
		std::cerr << "Erreur : Impossible de charger la police arial.ttf" << std::endl;
	}

	DialogueBox dialogueBox(font);
	map.setDialogueBox(&dialogueBox);

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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
			for (auto& npc : map.getAllNPCs()) {
				auto npcPtr = std::dynamic_pointer_cast<NPC>(npc);
				if (npcPtr && npcPtr->isNearPlayer(manager.player->getShape().getPosition().x,
					manager.player->getShape().getPosition().y)) {
					npcPtr->interact();
				}
			}
		}

		if (menuManager.isPlayButtonClicked()) {
			isPlaying = true;
		}

		if (isPlaying) {
			manager.player->update(deltaTime);
			manager.ButtonCheck(map, deltaTime);
			map.displayMap(window);
			dialogueBox.draw(window);
			manager.player->draw(window);
		}
		else {
			menu.drawMenu(window);
			menuManager.handleEvents();
		}

		std::cout << deltaTime << endl;

		window.display();
	}
}



