#include "npc.h"

NPC::NPC(float x, float y, float width, float height, std::shared_ptr<DialogueBox> dialogueBox) : MapElements(x, y, width, height, -1), dialogue(dialogueBox) {
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(sf::Color::Yellow); 
    shape.setPosition(x, y);
}

void NPC::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(dialogue->getText());
}

void NPC::interact() {
    dialogue->setText("Bonjour, tu doit être le nouvel employé.");
    dialogue->show(true, shape.getPosition());
}

bool NPC::isNearPlayer(float playerX, float playerY) {
    float detectionRadius = 200.0f; 
    return (std::abs(playerX - x) < detectionRadius && std::abs(playerY - y) < detectionRadius);
}
