#pragma once
#include "entity.h"
#include "raycast.h"

class Lamp : public Entity{
public:
	Lamp(int s, int h, Map& map);

	bool E = false;
	Raycast raycast;
	sf::VertexArray fov_Vizualisation;

	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	void illuminate(Map& map);
};

