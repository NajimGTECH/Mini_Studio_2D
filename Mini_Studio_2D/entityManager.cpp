#include "entityManager.h"

EntityManager::EntityManager(Map& map) {
	player = std::make_shared<Player>(100, 10, map);
	m_font.loadFromFile("Assets/Font/digit.ttf");

	std::vector<sf::Vector2f> buttonPositions = {
		{600, 250}, {847, 250}, {1094, 250},
		{600, 480}, {847, 480}, {1094, 480},
		{600, 710}, {847, 710}, {1094, 710}
	};

	for (int i = 1; i < 10; i++) {
		auto button = std::make_unique<Digit>(i);
		if (!button->texture.loadFromFile("Assets/Terminal/Digit" + std::to_string(button->value) + ".png")) {
			return;
		}
		button->shape.setPosition(buttonPositions[i-1]);
		button->shape.setTexture(&button->texture);
		m_buttons.push_back(std::move(button));
	}
}

void EntityManager::ButtonCheck(Map& map, float deltaTime) {
	for (auto& button : map.getAllButtons()) {
		if (player->getBase().getGlobalBounds().intersects(button->shape.getGlobalBounds())) {
			for (auto& door : map.getAllDoors()) {
				door->openDoor();
			}
			map.getAllButtons().clear();
		}
	}
}

bool EntityManager::TerminalCheck( Map& map) {
	for (auto& terminal : map.getAllTerminals()) {
		if (player->getShape().getGlobalBounds().intersects(terminal->shape.getGlobalBounds())) {
			return true;
		}
	}
	return false;
}

void EntityManager::displayTerminal(sf::RenderWindow& window){
	sf::Texture terminalT;
	if (!terminalT.loadFromFile("Assets/Terminal/terminal_cropped.png")) return;
	sf::RectangleShape darkback;
	darkback.setSize(sf::Vector2f(1920, 1080));
	darkback.setFillColor(sf::Color(0, 0, 0, 200));
	window.draw(darkback);
	sf::RectangleShape terminal;
	terminal.setSize(sf::Vector2f(1000,1000));
	terminal.setPosition(560, 100);
	terminal.setTexture(&terminalT);
	window.draw(terminal);
	code.setPosition(600, 180);
	code.setFont(m_font);
	window.draw(code);
	for (auto& button : m_buttons) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		bool isMouseOverButton = button->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
		bool isLeftClick = sf::Mouse::isButtonPressed(sf::Mouse::Left);

		if (isMouseOverButton && isLeftClick && !button->isClicked) {
			button->shape.setFillColor(sf::Color(100, 100, 100));
			if (code.getString().getSize() < 4) code.setString(code.getString() + std::to_string(button->value));
			button->isClicked = true;
		}
		else if (!isLeftClick) {
			if (!button->texture.loadFromFile("Assets/Terminal/Digit" + std::to_string(button->value) + ".png")) {
				return;
			}
			button->shape.setFillColor(sf::Color::White);
			button->shape.setTexture(&button->texture);
			button->isClicked = false;
		}

		window.draw(button->shape);
	}

}