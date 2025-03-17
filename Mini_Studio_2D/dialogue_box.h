#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class DialogueBox {
public:
    DialogueBox(sf::Font& font);

    void setText(const std::string& text);
    void draw(sf::RenderWindow& window);
    void show(bool visible, sf::Vector2f npcPosition);

private:
    sf::RectangleShape box;
    sf::Text dialogueText;
    bool isVisible;

    sf::Clock timer;
    float displayDuration = 3.0f;

    sf::Vector2f position; 
};
