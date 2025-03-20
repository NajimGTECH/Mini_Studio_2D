// inventory.cpp
#include "inventory.h"
#include <iostream>

Inventory::Inventory() : currentToolIndex(0) {}

void Inventory::addTool(std::shared_ptr<Entity> tool) {
    m_tools.push_back(tool);
}

void Inventory::switchTool(int toolIndex) {
    if (toolIndex >= 0 && toolIndex < m_tools.size()) {
        currentToolIndex = toolIndex;
        std::cout << "Équipement changé: " << toolIndex << std::endl;
    }
}

std::shared_ptr<Entity> Inventory::getActiveTool() {
    return m_tools.empty() ? nullptr : m_tools[currentToolIndex];
}

void Inventory::update(float deltaTime) {
    if (!m_tools.empty()) {
        m_tools[currentToolIndex]->update(deltaTime);
    }
}

void Inventory::draw(sf::RenderWindow& window) {
    if (!m_tools.empty()) {
        m_tools[currentToolIndex]->draw(window);
    }
}