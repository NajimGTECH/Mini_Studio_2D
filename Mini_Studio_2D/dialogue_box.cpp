#include "dialogue_box.h"

DialogueBox::DialogueBox(sf::Font& font) {
    box.setSize(sf::Vector2f(600, 100));
    box.setFillColor(sf::Color(0, 0, 0, 200)); // Fond semi-transparent
    box.setPosition(660, 800); // En bas de l’écran

    dialogueText.setFont(font);
    dialogueText.setCharacterSize(24);
    dialogueText.setFillColor(sf::Color::White);
    dialogueText.setPosition(680, 820); // Ajustement du texte

    isVisible = false;
}

void DialogueBox::setText(const std::string& text) {
    dialogueText.setString(text);
}

void DialogueBox::draw(sf::RenderWindow& window) {
    if (isVisible) {
        window.draw(box);
        window.draw(dialogueText);
    }
}

void DialogueBox::show(bool visible) {
    isVisible = visible;
}
