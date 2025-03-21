#pragma once

#include "raycast.h"
#include "player.h"

class Lamp : public Entity{
public:
	Lamp(sf::Vector2f s, int h, Map& map, Entity* owner);

	Raycast raycast;
	sf::VertexArray fov_Vizualisation;

	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	void illuminate();
	bool isMoving();

private:
	Entity* m_owner;
	void anim(float deltaTime) override;
};

