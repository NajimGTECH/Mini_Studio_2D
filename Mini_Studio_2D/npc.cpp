#include "npc.h"

NPC::NPC(float x, float y, float width, float height) : MapElements(x, y, width, height) {
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(sf::Color::Yellow); 
    shape.setPosition(x, y);
}

void NPC::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void NPC::interact() {
    std::cout << "PNJ : Bonjour, aventurier ! Besoin d'aide ?" << std::endl;
}

bool NPC::isNearPlayer(float playerX, float playerY) {
    return (std::abs(playerX - x) < 60 && std::abs(playerY - y) < 60);
}
