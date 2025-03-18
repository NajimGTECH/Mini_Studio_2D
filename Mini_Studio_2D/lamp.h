#pragma once
#include "entity.h"
#include "raycast.h"
#include "player.h"

class Lamp : public Entity{
public:
	Lamp(int s, int h, Map& map, Entity* owner);

	Raycast raycast;
	sf::VertexArray fov_Vizualisation;

	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	void illuminate();

private:
	Entity* m_owner;
};

