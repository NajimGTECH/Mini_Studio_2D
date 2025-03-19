#include "lamp.h"

Lamp::Lamp(int s, int h, Map& map, Entity* owner) : Entity(s, h, map) {
	m_texture.loadFromFile("Assets/Fournitures/lamp.png");
	m_texture1.loadFromFile("Assets/Fournitures/lamp1.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(2.0f, 2.0f);
	m_sprite.setPosition(100, 100);
	raycast.attachedEntity = this;
	fov_Vizualisation = sf::VertexArray(sf::TriangleFan, 0);
	m_owner = owner;
}

void Lamp::update(float deltaTime) {
	if (E) {
		illuminate();
	}
	for (const auto& intersection : raycast.intersections) {
		fov_Vizualisation.append(sf::Vertex(intersection, sf::Color(255, 150, 30, 100)));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		m_sprite.setTexture(m_texture1); // Changer la texture de la lampe
		m_sprite.setPosition(m_owner->getShape().getPosition().x - 50, m_owner->getShape().getPosition().y); // Déplacez la lampe vers la gauche
		raycast.attachedEntity->setOrientation(180.0f); // Mettre à jour l'orientation de l'entité
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		m_sprite.setTexture(m_texture); // Changer la texture de la lampe
		m_sprite.setPosition(m_owner->getShape().getPosition().x + 100, m_owner->getShape().getPosition().y); // Déplacez la lampe vers la droite
		raycast.attachedEntity->setOrientation(360.0f); // Mettre à jour l'orientation de l'entité
	}
}

void Lamp::draw(sf::RenderWindow& window) {
	if (E) {
		window.draw(m_sprite);
		window.draw(fov_Vizualisation);
	}
}

void Lamp::illuminate() {
	std::cout << "E" << std::endl;
	raycast.renderRay(m_map);
	fov_Vizualisation.clear();
	fov_Vizualisation.append(sf::Vertex(getSprite().getPosition() + sf::Vector2f(10, 30), sf::Color(255, 0, 0, 100)));
}