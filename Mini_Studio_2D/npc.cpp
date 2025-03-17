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
    dialogue.setText("Bonjour, tu doit �tre le nouvel employ�.");
    dialogue.show(true, shape.getPosition());
}

bool NPC::isNearPlayer(float playerX, float playerY) {
    float detectionRadius = 200.0f; 
    return (std::abs(playerX - x) < detectionRadius && std::abs(playerY - y) < detectionRadius);
}
