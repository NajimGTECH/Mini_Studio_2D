#pragma once
#include "entity.h"
#include "raycaster.h"

class Lamp : public Entity{
public:
	Lamp(int s, int h);

	Raycaster raycast;
	sf::VertexArray fov_Vizualisation;

	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	void illuminate();
};

