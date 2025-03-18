#include "lamp.h"

Lamp::Lamp(sf::Vector2f s, int h, Map& map, Entity* owner) : Entity(s, h, map) {
	
	m_texture.loadFromFile("Assets/Fournitures/lamp.png");
	m_texture1.loadFromFile("Assets/Fournitures/lamp1.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(2.0f, 2.0f);
	raycast.attachedEntity = this;
	fov_Vizualisation = sf::VertexArray(sf::TriangleFan, 0);
	m_owner = owner;

	m_shape.setSize({30.f, 30.f});
}

void Lamp::update(float deltaTime) {
	
	
	if (dynamic_cast<Player*>(m_owner)->getE()) {
		illuminate();
	}
	for (const auto& intersection : raycast.intersections) {
		fov_Vizualisation.append(sf::Vertex(intersection, sf::Color(255, 150, 30, 255)));
	}
	if (!dynamic_cast<Player*>(m_owner)->getWalkSide()) {
		m_sprite.setTexture(m_texture1); // Changer la texture de la lampe

		m_shape.setPosition(m_owner->getShape().getPosition().x - 50, m_owner->getShape().getPosition().y);
		m_sprite.setPosition(m_owner->getShape().getPosition().x - 50, m_owner->getShape().getPosition().y); // Déplacez la lampe vers la gauche

		raycast.attachedEntity->setOrientation(180.0f); // Mettre à jour l'orientation de l'entité
	}
	else if (dynamic_cast<Player*>(m_owner)->getWalkSide()) {
		m_sprite.setTexture(m_texture); // Changer la texture de la 

		m_shape.setPosition(m_owner->getShape().getPosition().x + 100, m_owner->getShape().getPosition().y);
		m_sprite.setPosition(m_owner->getShape().getPosition().x + 100, m_owner->getShape().getPosition().y); // Déplacez la lampe vers la droite

		raycast.attachedEntity->setOrientation(360.0f); // Mettre à jour l'orientation de l'entité
	}
}

void Lamp::draw(sf::RenderWindow& window) {
	if (dynamic_cast<Player*>(m_owner)->getE()) {
		
		window.draw(m_sprite);
		//window.draw(m_shape);

		if (!isCollisionDetected(sf::Vector2f(0, 0)))
		{
			window.draw(fov_Vizualisation);
		}
	}
}

void Lamp::illuminate() {
	if (!isCollisionDetected(sf::Vector2f(0, 0)))
	{
		raycast.renderRay(m_map);
		fov_Vizualisation.clear();
		fov_Vizualisation.append(sf::Vertex(getSprite().getPosition() + sf::Vector2f(10, 30), sf::Color(255, 0, 0, 255)));
	}

}


void Lamp::anim(float deltaTime)
{
}