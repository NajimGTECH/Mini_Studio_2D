#include "entityManager.h"
#include "player.h"

EntityManager::EntityManager(Map& map) {
    player = std::make_shared<Player>(sf::Vector2f(75, 130), 10, map);
    backpack = std::make_shared<Backpack>(map);


    if (!m_texturesLoaded) {
        if (!m_terminalT.loadFromFile("Assets/Terminal/terminal_cropped.png") ||
            !m_terminalGoodT.loadFromFile("Assets/Terminal/terminal_green.png") ||
            !m_terminalBadT.loadFromFile("Assets/Terminal/terminal_red.png")) {
            return;
        }
        m_texturesLoaded = true;
    }

    m_font.loadFromFile("Assets/Font/digit.ttf");

    std::vector<sf::Vector2f> buttonPositions = {
                    {870, 723},
        {746, 600}, {870, 604}, {992, 600},
        {746, 480}, {870, 480}, {992, 480},
        {750, 360}, {870, 360}, {992, 360},
    };


    auto erase_button = std::make_unique<Digit>(0, 1);
    if (!erase_button->texture.loadFromFile("Assets/Terminal/digitstar.png")) {
        return;
    }
    erase_button->shape.setTexture(&erase_button->texture);
    erase_button->shape.setPosition(sf::Vector2f(750, 720));
    m_buttons.push_back(std::move(erase_button));

    auto zero_button = std::make_unique<Digit>(0, 0);
    if (!zero_button->texture.loadFromFile("Assets/Terminal/digit0.png")) {
        return;
    }
    zero_button->shape.setTexture(&zero_button->texture);
    zero_button->shape.setPosition(buttonPositions[0]);
    m_buttons.push_back(std::move(zero_button));

    auto validate_button = std::make_unique<Digit>(0, 2);
    if (!validate_button->texture.loadFromFile("Assets/Terminal/digit#.png")) {
        return;
    }
    validate_button->shape.setTexture(&validate_button->texture);
    validate_button->shape.setPosition(sf::Vector2f(992, 720));
    m_buttons.push_back(std::move(validate_button));

    for (int i = 1; i < 10; i++) {
        auto button = std::make_unique<Digit>(i, 0);
        if (!button->texture.loadFromFile("Assets/Terminal/digit" + std::to_string(button->value) + ".png")) {
            return;
        }
        button->shape.setPosition(buttonPositions[i]);
        button->shape.setTexture(&button->texture);
        m_buttons.push_back(std::move(button));
    }
}

void EntityManager::generate(Map& map, int levelIndex)
{
    enemies.clear();

    //std::cout << "niveau : " << levelIndex << std::endl;

    char ch;
    std::vector<std::string> mapContent;
    std::string str;

    m_mapEFile.close();

    m_mapEFile.open("Maps/Level_" + std::to_string(levelIndex) + ".txt");

    if (!m_mapEFile) {
        std::cout << "erreur d'ouverture";
    }

    while (m_mapEFile.get(ch)) {
        if (ch == ' ' || ch == '\n')
        {
            if (!str.empty())
            {
                mapContent.push_back(str);
                str.clear();
                
            }
        }
        else
        {
            str += ch;
        }
    }

    if (!str.empty()) {
        mapContent.push_back(str);
    }
    if (!mapContent.empty()) {
        for (int y = 0; y < 17; y++)
        {
            for (int x = 0; x < 30; x++)
            {
                std::string checker = mapContent[x + 30 * y];
                sf::Vector2f spawnPos = sf::Vector2f(64 * (float)x, 64 * (float)y);

                if (checker[1] == 'E') {
                    enemies.push_back(std::make_shared<Enemy>(spawnPos, map));
                }
                else if (checker[1] == 'P') {
                    //std::cout << "Spawn pos: " << spawnPos.x << ", " << spawnPos.y << std::endl;
                    player->getShape().setPosition(spawnPos + sf::Vector2f{0.f, -30.f});
                    player->baseCoords = spawnPos;
                }
            }
        }
    }

    m_mapEFile.close();
}


void EntityManager::ButtonCheck(Map& map, float deltaTime) {
    for (auto& button : map.getAllButtons()) {
        if (player->getBase().getGlobalBounds().intersects(button->shape.getGlobalBounds())) {
            for (auto& door : map.getAllDoors()) {
                if (!door->opened && door->id == button->id) {
                    door->openDoor();
                    door->opened = true;
                }
            }
            map.getAllButtons().clear();
        }
    }
}

bool EntityManager::TerminalCheck(Map& map) {
    for (auto& terminal : map.getAllTerminals()) {
        if (player->getShape().getGlobalBounds().intersects(terminal->shape.getGlobalBounds())) {
            return true;
        }
    }
    return false;
}

void EntityManager::deathCheck(Map& map, TileManager& tilemanager){
    for (auto enemy : enemies) {
        if (player->getSprite().getGlobalBounds().intersects(enemy->getSprite().getGlobalBounds())) {
            map.createMap(map.currentLevel);
            generate(map, map.currentLevel);
            tilemanager.applyTileSet(map);

            player->getShape().setPosition(player->baseCoords);
        }
    }
}

void EntityManager::displayTerminal(sf::RenderWindow& window, Map& map) {
   
    static sf::Clock timer;
    static bool codeChecked = false;
    static bool codeValid = false;

   


    sf::Texture* currentTexture = &m_terminalT;
    if (codeChecked) {
        if (timer.getElapsedTime().asSeconds() < 1.0f) {
            currentTexture = codeValid ? &m_terminalGoodT : &m_terminalBadT;
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

    static int selectedButton = 1;
    static int delay = 20;
    static int cdelay = 50;

    if ((sf::Joystick::getAxisPosition(0, sf::Joystick::PovX) > 50 || sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 50) && delay < 0 && selectedButton != 12) {
        selectedButton += 1;
        delay = 20;
    }
    else if ((sf::Joystick::getAxisPosition(0, sf::Joystick::PovX) < -50 || sf::Joystick::getAxisPosition(0, sf::Joystick::X)  < -50) && delay < 0 && selectedButton != 1){
        selectedButton -= 1;
        delay = 20;
    }
    if ((sf::Joystick::getAxisPosition(0, sf::Joystick::PovY) > 50 || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < - 50) && delay < 0 && selectedButton != 10 && selectedButton != 11 && selectedButton != 12) {
        selectedButton += 3;
        delay = 20;
    }
    else if ((sf::Joystick::getAxisPosition(0, sf::Joystick::PovY) < -50 || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 50) && delay < 0 && selectedButton != 1 && selectedButton != 2 && selectedButton != 3) {
        selectedButton -= 3;
        delay = 20;
    }

    delay--;

    cdelay--;

    //std::cout << selectedButton << std::endl;


    for (auto& button : m_buttons) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        bool isMouseOverButton = button->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
        bool isLeftClick = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        bool isPressed = sf::Joystick::isButtonPressed(0, 0);
        bool isButtonSelected = button == m_buttons[selectedButton - 1];

        if (isButtonSelected) {
            button->shape.setOutlineThickness(10);
            button->shape.setOutlineColor(sf::Color::Red);
        }
        else {
            button->shape.setOutlineThickness(0);
        }


        if ((isMouseOverButton && isLeftClick && !button->isClicked) || (isButtonSelected && isPressed && !button->isClicked && cdelay < 0)) {
            cdelay = 50;
            button->shape.setFillColor(sf::Color(100, 100, 100));
            delay = 30;

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
