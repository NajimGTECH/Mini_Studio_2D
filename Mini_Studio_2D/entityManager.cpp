#include "entityManager.h"

EntityManager::EntityManager(Map& map) {
	player = std::make_shared<Player>(100, 10, map);
	m_font.loadFromFile("Assets/Font/digit.ttf");

	std::vector<sf::Vector2f> buttonPositions = {
					{870, 723},
		{746, 600}, {870, 604}, {992, 600},
		{746, 480}, {870, 480}, {992, 480},
		{750, 360}, {870, 360}, {992, 360},
	};

	for (int i = 0; i < 10; i++) {
		auto button = std::make_unique<Digit>(i, 0);
		if (!button->texture.loadFromFile("Assets/Terminal/digit" + std::to_string(button->value) + ".png")) {
			return;
		}
		button->shape.setPosition(buttonPositions[i]);
		button->shape.setTexture(&button->texture);
		m_buttons.push_back(std::move(button));
	}
	auto erase_button = std::make_unique<Digit>(0, 1);
	if (!erase_button->texture.loadFromFile("Assets/Terminal/digitstar.png")) {
		return;
	}
	erase_button->shape.setTexture(&erase_button->texture);
	erase_button->shape.setPosition(sf::Vector2f(750, 720));
	m_buttons.push_back(std::move(erase_button));
	
	auto validate_button = std::make_unique<Digit>(0, 2);
	if (!validate_button->texture.loadFromFile("Assets/Terminal/digit#.png")) {
		return;
	}
	validate_button->shape.setTexture(&validate_button->texture);
	validate_button->shape.setPosition(sf::Vector2f(992, 720));
	m_buttons.push_back(std::move(validate_button));
}

void EntityManager::ButtonCheck(Map& map, float deltaTime) {
	for (auto& button : map.getAllButtons()) {
		if (player->getBase().getGlobalBounds().intersects(button->shape.getGlobalBounds())) {
			for (auto& door : map.getAllDoors()) {
				if (!door->opened) {
					door->openDoor();
					door->opened = true;
				}
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

void EntityManager::displayTerminal(sf::RenderWindow& window, Map& map) {
    static sf::Texture terminalT, terminalGoodT, terminalBadT;
    static bool texturesLoaded = false;
    static sf::Clock timer;
    static bool codeChecked = false;
    static bool codeValid = false;

    if (!texturesLoaded) {
        if (!terminalT.loadFromFile("Assets/Terminal/terminal_cropped.png") ||
            !terminalGoodT.loadFromFile("Assets/Terminal/terminal_green.png") ||  
            !terminalBadT.loadFromFile("Assets/Terminal/terminal_red.png")) {   
            return;
        }
        texturesLoaded = true;
    }

    
    sf::Texture* currentTexture = &terminalT;
    if (codeChecked) {
        if (timer.getElapsedTime().asSeconds() < 1.0f) {
            currentTexture = codeValid ? &terminalGoodT : &terminalBadT;
        }
        else {
            codeChecked = false;  
        }
    }

    sf::RectangleShape darkback;
    darkback.setSize(sf::Vector2f(1920, 1080));
    darkback.setFillColor(sf::Color(0, 0, 0, 200));
    window.draw(darkback);

    sf::RectangleShape terminal;
    terminal.setSize(sf::Vector2f(1000, 1000));
    terminal.setPosition(460, 50);
    terminal.setTexture(currentTexture);
    window.draw(terminal);

    code.setPosition(750, 190);
    code.setCharacterSize(100);
    code.setLetterSpacing(5);
    code.setFont(m_font);
    window.draw(code);


    for (auto& button : m_buttons) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        bool isMouseOverButton = button->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
        bool isLeftClick = sf::Mouse::isButtonPressed(sf::Mouse::Left);

        if (isMouseOverButton && isLeftClick && !button->isClicked) {
            button->shape.setFillColor(sf::Color(100, 100, 100));

            if (code.getString().getSize() < 4 && button->type == 0) {
                code.setString(code.getString() + std::to_string(button->value));
            }
            else if (button->type == 1) {
                code.setString("");
            }
            else if (button->type == 2) {  
                codeChecked = true;
                codeValid = (code.getString() == map.getCode());
                timer.restart();  

                if (codeValid) {
                    for (auto doors : map.getAllDoors()) {
                        if (!doors->opened) {
                            doors->openDoor();
                            doors->opened = true;
                        }
                    }
                }
            }
            button->isClicked = true;
        }
        else if (!isLeftClick) {
            button->shape.setTexture(&button->texture);
            button->shape.setFillColor(sf::Color::White);
            button->isClicked = false;
        }

        window.draw(button->shape);
    }
}
