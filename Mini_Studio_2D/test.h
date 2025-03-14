#pragma once

#include <SFML/Graphics.hpp>
#include "window.h" 
#include "entity.h"
#include "entityManager.h"
#include "map.h"
#include <cmath>

class test {
    public:
        test() {};
        Entity* attachedEntity;
        std::vector<sf::Vector2f> intersections;

		int CELL_SIZE = 60;
        void renderRay(Map& map);
        float degToRad(float degree);
};

