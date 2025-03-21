#include "npc.h"

NPC::NPC(float x, float y, float width, float height, std::shared_ptr<DialogueBox> dialogueBox) : MapElements(x, y, width, height, -1), dialogue(dialogueBox) {

    if (!m_texture.loadFromFile("Assets/Enemy/patron.png")) return;
    shape.setTexture(&m_texture);

    shape.setSize(sf::Vector2f(width, height * 2));
    shape.setPosition(x, y - 50);
    shape.setScale(1.4, 1.4);
}

void NPC::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(dialogue->getText());
}

void NPC::interact() {
    dialogue->setText("Ah, you must be the new recruit! Welcome to Nova Lab.");
    dialogue->show(true, shape.getPosition());
}

bool NPC::isNearPlayer(float playerX, float playerY) {
    float detectionRadius = 200.0f; 
    return (std::abs(playerX - x) < detectionRadius && std::abs(playerY - y) < detectionRadius);
}
