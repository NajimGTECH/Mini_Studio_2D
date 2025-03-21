#pragma once

#include "raycast.h"
#include "player.h"
#include "clipper2/clipper.h"

class Lamp : public Entity{
public:
	Lamp(sf::Vector2f s, int h, Map& map, Entity* owner);

	Raycast raycast;
	sf::VertexArray fov_Vizualisation;

	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	void illuminate();
	Clipper2Lib::Point64 toPoint64(const sf::Vector2f& point);
	sf::Vector2f toSfVector2f(const Clipper2Lib::Point64& point);

	bool isMoving();

private:
	Entity* m_owner;
	void anim(float deltaTime) override;
	sf::VertexArray m_shadowShape;
};

