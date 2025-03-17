#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "mapElements.h"
#include "dialogue_box.h"

class NPC : public MapElements {
public:
    NPC(float x, float y, float width, float height, DialogueBox& dialogueBox);
    void interact();

    void draw(sf::RenderWindow& window) override;
    bool isNearPlayer(float playerX, float playerY);

private:
    DialogueBox& dialogue;
};
