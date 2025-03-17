#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "mapElements.h"

class NPC : public MapElements {
public:
    NPC(float x, float y, float width, float height);

    void draw(sf::RenderWindow& window) override;
    void interact();

    bool isNearPlayer(float playerX, float playerY);
};
