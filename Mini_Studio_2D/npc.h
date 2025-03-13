#pragma once

#include "entity.h"
#include <SFML/Graphics.hpp>
#include <vector>

class NPC : public Entity {
public:
    NPC(int size, int hp, Map& map, sf::Vector2f position);

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    bool isPlayerNearby(sf::Vector2f playerPos);
    std::string getDialogue(float deltaTime);

private:
    sf::Text dialogueText;
    sf::RectangleShape dialogueBox;
    std::vector<std::string> dialogues;
    int dialogueIndex = 0;
    float timeSinceLastDialogue = 2.0f;
    float dialogueInterval = 2.0f;
};


