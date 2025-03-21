#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <SFML/Graphics.hpp>

#include "menu.h"
#include "map.h"
#include "tileManager.h"
#include "entityManager.h"

class MenuManager {
public:
    MenuManager(RenderWindow& window, Menu& menu, Map& map, EntityManager& entityManager, TileManager& tileManager);
    void handleEvents(float deltaTime);
    bool isPlayButtonClicked();

private:
    RenderWindow& window;
    Menu& menu;
    bool gameIsLaunch = false;
    Map& m_map;
    EntityManager& m_entityManager;
    TileManager& m_tilemanager;
};

#endif
