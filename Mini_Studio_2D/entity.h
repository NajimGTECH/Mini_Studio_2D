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


	float getFov() const;
	float getOrientation() const;

	sf::RectangleShape& getShape();
	sf::RectangleShape& getBase();
	sf::Sprite& getSprite();
	sf::Texture& getTexture();
	sf::Texture setTexture(sf::Texture texture);
	float setOrientation(float orientation);
	sf::Vector2f getDirection();
	

	bool isCollisionDetected(sf::Vector2f targetVelocity);

protected:


	sf::Vector2f m_direction = { 0, 0 };



	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::RectangleShape m_shape;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::Texture m_texture1;
	sf::RectangleShape m_base;
	sf::Vector2f m_size;
	int m_hp;

	Map& m_map;
	float m_fov = 60.0f;
	float m_orientation = 360.0f;

	bool E = false;
};

