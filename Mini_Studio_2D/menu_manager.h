#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <SFML/Graphics.hpp>
#include "menu.h"

class MenuManager {
public:
    MenuManager(RenderWindow& window, Menu& menu);
    void handleEvents();
    bool isPlayButtonClicked();

private:
    RenderWindow& window;
    Menu& menu;
    bool gameIsLaunch = false;
    
};

#endif
