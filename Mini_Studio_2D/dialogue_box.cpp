#include "dialogue_box.h"

DialogueBox::DialogueBox(sf::Font& font) {
    box.setSize(sf::Vector2f(600, 100));
    box.setFillColor(sf::Color(0, 0, 0, 200)); 
    box.setPosition(660, 800); 

    dialogueText.setFont(font);
    dialogueText.setCharacterSize(24);
    dialogueText.setFillColor(sf::Color::White);
    dialogueText.setPosition(680, 820); 

    isVisible = false;
}

void DialogueBox::setText(const std::string& text) {
    dialogueText.setString(text);
}

void DialogueBox::draw(sf::RenderWindow& window) {
    if (isVisible) {
        if (timer.getElapsedTime().asSeconds() > displayDuration) {
            isVisible = false;
            return;
        }

        window.draw(box);
        window.draw(dialogueText);
    }
}

void DialogueBox::show(bool visible, sf::Vector2f npcPosition) {
    isVisible = visible;
    if (visible) {
        timer.restart();
        position = { npcPosition.x, npcPosition.y - 50 };
        box.setPosition(position.x - 30, position.y - 20);
        dialogueText.setPosition(position.x, position.y - 10);
    }
}

sf::Text& DialogueBox::getText()
{
    return dialogueText;
}


