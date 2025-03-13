#pragma once
#include "entity.h"
#include "test.h"

class Lamp : public Entity{
public:
	Lamp(int s, int h, Map& map);

	test raycast;
	sf::VertexArray fov_Vizualisation;

	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	void illuminate(Map& map);
};

