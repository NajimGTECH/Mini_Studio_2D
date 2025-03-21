#include "menu_manager.h"
#include <iostream>

using namespace sf;
using namespace std;

MenuManager::MenuManager(RenderWindow& window, Menu& menu, Map& map, EntityManager& entityManager, TileManager& tile)
    : window(window), menu(menu), m_map(map), m_tilemanager(tile), m_entityManager(entityManager)
{
    menu.switchToMain();
}

void MenuManager::handleEvents(float deltaTime) {

    static float cooldownMax = .1f;
    static float cooldown = cooldownMax;

    Vector2f mousePos = Vector2f(Mouse::getPosition(window));
    menu.update(mousePos);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && cooldown >= cooldownMax) {
        if (menu.isOptionClicked(mousePos)) {
            int option = menu.getSelectedIndex();

            if (menu.menuState == MenuState::MAIN) {
                if (option == 0) {
                    cout << "Lancer la partie !" << endl;
                    menu.startGame = true; // Indique que le jeu doit commencer
                    menu.stopmenuMusic();

                    if (!m_map.loaded) {
                        m_map.createMap(m_map.currentLevel);
                        m_entityManager.generate(m_map, m_map.currentLevel);
                        m_map.loaded = true;
                        m_tilemanager.applyTileSet(m_map);
                        //std::cout << "map loaded" << std::endl;
                    }
                }
                else if (option == 1) {
                    menu.switchToOptions();
                }
                else if (option == 2) {
                    menu.switchToCustomLevels();
                }
                else if (option == 3) {
                    cout << "Quitter le jeu." << endl;
                    window.close();
                }
            }
            else if (menu.menuState == MenuState::OPTIONS) {
                if (option == 0) {
                    menu.switchToSound();
                }
                else if (option == 1) {
                    menu.switchToControls();
                }
                else if (option == 2) {
                    menu.switchToMain();
                }
            }
            else if (menu.menuState == MenuState::CONTROLS) {
                if (option == 0) {
                    menu.switchToOptions();
                }
            }
            else if (menu.menuState == MenuState::SOUND) {
                if (option == 0) {
                    float volume = menu.menuMusic.getVolume();

                    volume = max(0.5f, volume - 5.f);

                    menu.menuMusic.setVolume(volume);
                    menu.switchToSound();
                }
                else if (option == 1) {
                    float volume = menu.menuMusic.getVolume();;

                    volume = min(100.5f, volume + 5.f);

                    menu.menuMusic.setVolume(volume);
                    menu.switchToSound();
                }
                else if (option == 2) {
                    menu.switchToOptions();
                }
            }
            else if (menu.menuState == MenuState::CUSTOM_LEVELS) 
            {
                if (option == 0) 
                {
                    menu.startGame = true; // Indique que le jeu doit commencer
                    menu.stopmenuMusic();

                    auto text = menu.getTextFromOption(option + 1); //the element 0 is the title explainging how the custom levels system works
                    std::string customLevelPath = text.getString() + ".txt";
                    m_map.createCustomLevel(customLevelPath);
                    m_map.loaded = true;
                }
                else if (option == 5) 
                {
                    menu.switchToMain();
                }
            }
        }
        cooldown = 0;
    }

    cooldown += deltaTime;
}

bool MenuManager::isPlayButtonClicked() {
    return menu.startGame;
}
