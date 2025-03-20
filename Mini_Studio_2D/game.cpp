#include "game.h"
#include "menu_manager.h"

Game::Game() { m_terminal = false; }

void Game::run() {
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "The Perfect Job");
	window.setFramerateLimit(120);

	sf::Image icon;
	icon.loadFromFile("Assets/Logo.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());


	Map map;
	EntityManager manager(map);
	MainClock mainClock(10);
	TileManager tilemanager;

	/*Closet closet(60, 60, map);
	Desk desk(60, 60, map);
	Box box(60, 60, map);
	BookShelf bookShelf(60, 60, map);
	Chair chair(60, 60, map);
	Shelf shelf(60, 60, map);*/
	Menu menu(1920, 1080);
	Screen screen(map);
	MenuManager menuManager(window, menu, map,  tilemanager);

	EntityManager manager(map);

	sf::Clock clock;
	float deltaTime = 0.0f;
	
	sf::Font font;
	if (!font.loadFromFile("Assets/TextMenu/SolarPunk.otf")) {
		std::cerr << "Erreur : Impossible de charger la police SolarPunk.otf" << std::endl;
	}

	bool menub = true;
	bool isPlaying = false;


	while (window.isOpen()) {

		window.clear();
		deltaTime = clock.restart().asSeconds();

		if (manager.player->getShape().getPosition().x > 1950 || manager.player->getShape().getPosition().y > 1100)
		{
			map.currentLevel++;
			map.createMap(map.currentLevel);
			manager.generate(map, map.currentLevel);

			tilemanager.applyTileSet(map);
			map.loaded = true;
			if (map.currentLevel == 1) {
				manager.player->getShape().setPosition(600, -100);
			}
			else
			manager.player->getShape().setPosition(100, 700);
		}

		manager.deathCheck(map);

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::R) {
					manager.player->reverseE();
				}
			}
		}
		if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::E) {
				if (manager.TerminalCheck(map)) {
					m_terminal = !m_terminal;
					manager.code.setString("");
				}
			}
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
			for (auto& npc : map.getAllNPCs()) {
				auto npcPtr = std::dynamic_pointer_cast<NPC>(npc);
				if (npcPtr && npcPtr->isNearPlayer(manager.player->getShape().getPosition().x, manager.player->getShape().getPosition().y)) {
					npcPtr->interact();
				}
			}
		}

		map.displayMap(window);
		
		if (menuManager.isPlayButtonClicked()) {
			isPlaying = true;
			menub = false;
		}



		if (isPlaying) {

			mainClock.updateClock(window, deltaTime);
			map.updateFurnitures(deltaTime);
			manager.ButtonCheck(map, deltaTime);

			for (auto enemy : manager.enemies) {
				enemy->draw(window);
				enemy->update(deltaTime);
			}

			if (map.currentLevel == 0) {
				if (manager.backpack) {
					manager.backpack->update(deltaTime);

					manager.backpack->draw(window);
					if (manager.player->getShape().getGlobalBounds().intersects(manager.backpack->getSprite().getGlobalBounds())) {
						manager.backpack.reset();
						manager.player->obtainBag();
					}
				}
			}

			map.displayMap(window);
			manager.player->draw(window);

			if (!m_terminal) {
				manager.player->update(deltaTime);
			}
			else if (m_terminal) {
				manager.displayTerminal(window, map);
			}
		}
		else if (menub) {
			menu.drawMenu(window);
			menuManager.handleEvents(deltaTime);
		}

		screen.draw(window);
		/*closet.draw(window);
		desk.draw(window);*/
		/*box.draw(window);*/
		/*bookShelf.draw(window);*/
		/*chair.draw(window);*/
		/*shelf.draw(window);*/

		window.display();
	}
}



