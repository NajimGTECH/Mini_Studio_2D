#include "npc.h"

NPC::NPC(int size, int hp, Map& map, sf::Vector2f position) : Entity(size, hp, map) {
    m_shape.setPosition(position);
    m_shape.setFillColor(sf::Color::Blue);

    dialogues = {
        "YOKOSO",
        "MONSTER Hunter Wild sous coté de fou",
        "J'aime la vie"
        "En fait Luden c'est un passif mytique"
    };

    dialogueBox.setSize(sf::Vector2f(400, 80));
    dialogueBox.setFillColor(sf::Color(0, 0, 0, 150));
    dialogueBox.setPosition(position.x - 50, position.y - 60);
}

void NPC::draw(sf::RenderWindow& window) {
    window.draw(m_shape);
}

void NPC::update(float deltaTime) {};

bool NPC::isPlayerNearby(sf::Vector2f playerPos) {
    return (std::abs(m_shape.getPosition().x - playerPos.x) < 100 &&
        std::abs(m_shape.getPosition().y - playerPos.y) < 100);
}

std::string NPC::getDialogue() {
    dialogueIndex = (dialogueIndex + 1) % dialogues.size();
    return dialogues[dialogueIndex];
}
