#include "raycaster.h"

#define PI 3.14159265

sf::Vector2f operator-(const sf::Vector2f& vector, float value)
{
    return { vector.x - value, vector.y - value };
}

sf::Vector2f operator*(const sf::Vector2f& vector1, const sf::Vector2f& vector2)
{
    return { vector1.x * vector2.x, vector1.y * vector2.y };
}

sf::Vector2f operator/(const sf::Vector2f& vector, float value)
{
    return { vector.x / value, vector.y / value };
}

sf::Vector2f normalize(const sf::Vector2f& vector) {

    float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);

    if (length != 0) {
        return sf::Vector2f(vector.x / length, vector.y / length);
    }

    return sf::Vector2f(0.f, 0.f);
}


void Raycaster::renderRay(Grid& grid)
{
    intersections.clear();
    sf::Vector2f rayStart = attachedEntity->shape.getPosition(); // attachedEntity->m_shape.getPosition(); ( get a faire)
    float startAngle = attachedEntity->orientation - attachedEntity->fov / 2.f; // a faire ( git : arientation et fov)

	const float STEP_ANGLE = attachedEntity->fov / window::WINDOW_WIDTH; // a voir si juste taille de window actuelle ou namespace pour global

    int side = 0;

    for (int i = 0; i <= window::WINDOW_WIDTH; i++)
    {
        sf::Vector2f rayDir = normalize({ cos(degToRad(startAngle + i * STEP_ANGLE)), sin(degToRad(startAngle + i * STEP_ANGLE)) });

        sf::Vector2f rayUnitStepSize = {
           sqrt(1 + (rayDir.y / rayDir.x) * (rayDir.y / rayDir.x)), //sqrt(1 + (rayDir.y / rayDir.x)^2
           sqrt(1 + (rayDir.x / rayDir.y) * (rayDir.x / rayDir.y))  //sqrt(1 + (rayDir.x / rayDir.y)^2
        };

        sf::Vector2f mapCheck = {
             static_cast<int>(rayStart.x / CELL_SIZE) * (float)CELL_SIZE, // taille de la map divisée par le nombre de caractère 
             static_cast<int>(rayStart.y / CELL_SIZE) * (float)CELL_SIZE
        };
        sf::Vector2f rayLength;

        sf::Vector2f step;

        //check horizontal lines
        if (rayDir.x < 0)
        {
            step.x = -1;
            rayLength.x = (rayStart.x - mapCheck.x) * rayUnitStepSize.x;
        }
        else
        {
            step.x = 1;
            rayLength.x = ((mapCheck.x + 1) - rayStart.x) * rayUnitStepSize.x;
        }

        //check vertical lines
        if (rayDir.y < 0)
        {
            step.y = -1;
            rayLength.y = (rayStart.y - mapCheck.y) * rayUnitStepSize.y;
        }
        else
        {
            step.y = 1;
            rayLength.y = ((mapCheck.y + 1) - rayStart.y) * rayUnitStepSize.y;
        }


        bool isTileFound = false;
        float maxDistance = 250.f;
        float distance = 0.f;

        while (!isTileFound && distance < maxDistance)
        {
            if (rayLength.x < rayLength.y)
            {
                mapCheck.x += step.x;
                distance = rayLength.x;
                rayLength.x += rayUnitStepSize.x;
                side = 0;
            }
            else
            {
                mapCheck.y += step.y;
                distance = rayLength.y;
                rayLength.y += rayUnitStepSize.y;
                side = 1;
            }

            int gridX = static_cast<int>(mapCheck.x / CELL_SIZE);
            int gridY = static_cast<int>(mapCheck.y / CELL_SIZE);

            if (gridX >= 0 && gridX < GRID_WIDTH && gridY >= 0 && gridY < GRID_HEIGHT) // a calculé en fonction de map et tiles
            {
                if (!grid.cells[gridY][gridX].walkable) // faire avec une autre nos collisions
                {
                    isTileFound = true;
                }
            }
            else
            {
                isTileFound = true;
            }
        }

        intersections.push_back(rayStart + rayDir * distance);
    }
    //return intersections;
}

float Raycaster::degToRad(float degree)
{
    return degree * PI / 180;
}
