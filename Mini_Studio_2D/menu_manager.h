#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <SFML/Graphics.hpp>

#include "menu.h"
#include "map.h"

class MenuManager {
public:
    MenuManager(RenderWindow& window, Menu& menu, Map& map);
    void handleEvents(float deltaTime);
    bool isPlayButtonClicked();

private:
    RenderWindow& window;
    Menu& menu;
    bool gameIsLaunch = false;
    Map& m_map;
};

#endif
