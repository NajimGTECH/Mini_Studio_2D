#pragma once

#include <SFML/Graphics.hpp>

#include "map.h"

class Entity
{
public:



	Entity(sf::Vector2f size, int hp, Map& map);

	virtual void update(float deltaTime) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void anim(float deltatime) = 0;


	sf::RectangleShape& getShape();
	sf::RectangleShape& getBase();
	sf::Sprite& getSprite();
	sf::Vector2f getDirection();


	bool hasBag();
	bool isCollisionDetected(sf::Vector2f targetVelocity);

protected:

	sf::Clock m_animC;

	sf::Vector2f m_coeffAnim;
	sf::Vector2f m_animVect = sf::Vector2f(0,0);
	sf::Vector2f m_direction = { 0, 0 };

	bool m_hasBag = false;

	float m_scaling;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::RectangleShape m_shape;
	sf::RectangleShape m_base;
	sf::Vector2f m_size;
	int m_hp;

	Map& m_map;
};

