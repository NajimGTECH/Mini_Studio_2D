#pragma once
#include <SFML/Graphics.hpp>
#include "window.h" 
#include "entity.h"
#include "entityManager.h"
#include "map.h"
#include <cmath>

class Raycaster {
public:
        Raycaster() {};
        void renderRay(); // suremnet pas besoin d'argument : utile que pour collisions
        float degToRad(float degree);
        std::vector<int> getMapCollision();

        Map map;
		const int CELL_SIZE = 64;
        std::vector<int> mapCollision;
        Entity* attachedEntity;
        std::vector<sf::Vector2f> intersections;
};

