/*
#pragma once
#include <SFML/Graphics.hpp>
#include "window.h" // a voir si je garde
#include "entity.h"
#include <cmath>

class Raycaster {

    public:
        Raycaster() {};
        std::shared_ptr<Entity> attachedEntity;
        std::vector<sf::Vector2f> intersections;

        void renderRay(Grid& grid); // suremnet pas besoin d'argument : utile que pour collisions
        float degToRad(float degree);
    };
};

*/