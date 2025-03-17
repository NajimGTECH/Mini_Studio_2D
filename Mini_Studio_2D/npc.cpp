#include "npc.h"

NPC::NPC(float x, float y, float width, float height, DialogueBox& dialogueBox) : MapElements(x, y, width, height), dialogue(dialogueBox) {
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(sf::Color::Yellow); 
    shape.setPosition(x, y);
}

void NPC::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void NPC::interact() {
    dialogue.setText("PNJ : Bonjour, aventurier !");
    dialogue.show(true);
}

bool NPC::isNearPlayer(float playerX, float playerY) {
    return (std::abs(playerX - x) < 60 && std::abs(playerY - y) < 60);
}
