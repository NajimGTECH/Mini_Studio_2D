#include "entity.h"

Entity::Entity(sf::Vector2f size, int hp, Map& map) : m_size(size), m_hp(hp), m_map(map)
{

	m_shape.setSize(m_size);
	m_shape.setFillColor(sf::Color::Green);
}

sf::RectangleShape& Entity::getShape() {
	return m_shape;
}

sf::Sprite& Entity::getSprite() {
	return  m_sprite;
}

sf::RectangleShape& Entity::getBase() {
	return m_base;
}

sf::Vector2f Entity::getDirection()
{
	return m_direction;
}

sf::Texture& Entity::getTexture() {
	return m_texture;
}

void Entity::anim(float deltatime)
{
}

float Entity::getFov() const {
	return m_fov;
}

sf::Texture Entity::setTexture(sf::Texture texture) {
	m_texture = texture;
	return m_texture;
}

float Entity::getOrientation() const {
	return m_orientation;
}

float Entity::setOrientation(float orientation) {
	m_orientation = orientation;
	return m_orientation;
}


bool Entity::hasBag()
{
	return m_hasBag;
}

bool Entity::isCollisionDetected(sf::Vector2f targetVelocity)
{
	sf::RectangleShape hitboxDummy;
	hitboxDummy.setSize(m_shape.getSize());
	hitboxDummy.setPosition(m_shape.getPosition() + targetVelocity);

	for (auto& wall : m_map.getAllWalls()) {

		if (hitboxDummy.getGlobalBounds().intersects(wall->shape.getGlobalBounds()))
		{
			return true;
		}
	}
	for (auto& door : m_map.getAllDoors()) {

		if (hitboxDummy.getGlobalBounds().intersects(door->shape.getGlobalBounds()))
		{
			return true;
		}
	}
	return false;
}