// inventory.h
#pragma once
#include <vector>
#include <memory>
#include "entity.h"

class Inventory {
public:
    Inventory();
    void addTool(std::shared_ptr<Entity> tool);
    void switchTool(int toolIndex);
    std::shared_ptr<Entity> getActiveTool();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

private:
    std::vector<std::shared_ptr<Entity>> m_tools;
    int currentToolIndex;
};