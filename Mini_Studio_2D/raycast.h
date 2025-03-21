#pragma once

#include <SFML/Graphics.hpp>
#include "window.h" 
#include "mapElements.h"
#include <cmath>
#include "entity.h"

class Raycast {
    public:

        Entity* attachedEntity = 0;
        std::vector<sf::Vector2f> intersections;

		int CELL_SIZE = 64;
        void renderRay(Map& map);
        float degToRad(float degree);
};

