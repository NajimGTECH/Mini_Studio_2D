#include "menu_manager.h"
#include <iostream>

using namespace sf;
using namespace std;

MenuManager::MenuManager(RenderWindow& window, Menu& menu)
    : window(window), menu(menu) {
}

void MenuManager::handleEvents() {
    Vector2f mousePos = Vector2f(Mouse::getPosition(window));
    menu.update(mousePos);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (menu.isOptionClicked(mousePos)) {
            int option = menu.getselectedIndex();

            if (menu.menuState == MenuState::MAIN) {
                if (option == 0) {
                    cout << "Lancer la partie !" << endl;
                    menu.startGame = true; // Indique que le jeu doit commencer
                }
                else if (option == 1) {
                    menu.switchToOptions();
                }
                else if (option == 2) {
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
                    volume = max(0.0f, volume - 10.f);
                    menu.menuMusic.setVolume(volume);
                    menu.switchToSound();
                }
                else if (option == 1) {
                    float volume = menu.menuMusic.getVolume();
                    volume = min(100.0f, volume + 10.f);
                    menu.menuMusic.setVolume(volume);
                    menu.switchToSound();
                }
                else if (option == 2) {
                    menu.switchToOptions();
                }
            }
        }
    }
}

bool MenuManager::isPlayButtonClicked() {
    return menu.startGame;
}
