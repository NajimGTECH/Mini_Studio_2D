#include "game.h"
#include "menu_manager.h"

Game::Game() { m_terminal = false; }

void Game::run() {
	

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "The Perfect Job", sf::Style::Fullscreen);
	window.setFramerateLimit(120);

	sf::Image icon;
	icon.loadFromFile("Assets/Logo.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	Map map;
	EntityManager manager(map);
	TileManager tilemanager;

	Menu menu(1920, 1080);
	MenuManager menuManager(window, menu, map, manager, tilemanager);

	Screen screen(map);
	MainClock mainClock(400);

	sf::Clock clock;
	float deltaTime = 0.0f;
	
	sf::Font font;
	if (!font.loadFromFile("Assets/TextMenu/SolarPunk.otf")) {
		std::cerr << "Erreur : Impossible de charger la police SolarPunk.otf" << std::endl;
	}

	bool menub = true;
	bool isPlaying = false;

	int wait = 0.3;

	while (window.isOpen()) {


		window.clear();
		deltaTime = clock.restart().asSeconds();

		if (manager.player->getShape().getPosition().x > 1950 || manager.player->getShape().getPosition().y > 1100)
		{
			map.currentLevel++;
			screen.plusCountLevel();
			map.createMap(map.currentLevel);
			manager.generate(map, map.currentLevel);

			tilemanager.applyTileSet(map);
			map.loaded = true;
			//if (map.currentLevel == 1) {
			//	manager.player->getShape().setPosition(600, -100);
			//}
			//else
			//manager.player->getShape().setPosition(192, 200);
			//manager.player->getSprite().setPosition(192, 200);
		}

		manager.deathCheck(map, tilemanager);

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.key.code == sf::Mouse::Left) {
					manager.player->reverseE();
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
			if (sf::Joystick::isButtonPressed(0, 3)) {
				if (manager.TerminalCheck(map) && wait <= 0) {
					m_terminal = !m_terminal;
					manager.code.setString("");
					wait = 0.3;
				}
				else if (manager.TerminalCheck(map) && wait > 0) wait -= deltaTime;
			}
		}
		

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Joystick::isButtonPressed(0, 2)) {
			map.createMap(map.currentLevel);
			manager.generate(map, map.currentLevel);
			tilemanager.applyTileSet(map);

			manager.player->getShape().setPosition(manager.player->baseCoords);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) || sf::Joystick::isButtonPressed(0,3)) {
			for (auto& npc : map.getAllNPCs()) {
				auto npcPtr = std::dynamic_pointer_cast<NPC>(npc);
				if (npcPtr && npcPtr->isNearPlayer(manager.player->getShape().getPosition().x, manager.player->getShape().getPosition().y)) {
					npcPtr->interact();
				}
			}
		}

		
		if (menuManager.isPlayButtonClicked()) {
			isPlaying = true;
			menub = false;
		}



		if (isPlaying) {

			if (mainClock.getIsAlive() == 0 || screen.getCountLevel() == 10) {
				isPlaying = false;
			}

			mainClock.updateClock(window, deltaTime);
			map.updateFurnitures(deltaTime);
			manager.ButtonCheck(map, deltaTime);
			map.displayMap(window);
			manager.player->draw(window);

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

		window.display();
	}
}



