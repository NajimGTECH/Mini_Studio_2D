#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class DialogueBox {
public:
    DialogueBox(sf::Font& font);
    void setText(const std::string& text);
    void draw(sf::RenderWindow& window);
    void show(bool visible);

private:
    sf::RectangleShape box;
    sf::Text dialogueText;
    bool isVisible;
};
