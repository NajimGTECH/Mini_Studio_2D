#include "lamp.h"

Lamp::Lamp(int s, int h, Map& map) : Entity(s, h, map) {
	m_texture.loadFromFile("Assets/Fournitures/lamp.png");
	m_texture1.loadFromFile("Assets/Fournitures/lamp1.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(2.0f, 2.0f);
	m_sprite.setPosition(100, 100);
	fov_Vizualisation = sf::VertexArray(sf::TriangleFan, 0);

}

void Lamp::update(float deltaTime) {}

void Lamp::draw(sf::RenderWindow& window) {
	window.draw(m_sprite);
	if (!E) {
			window.draw(fov_Vizualisation);
	}
}

void Lamp::illuminate(Map& map) {

	if (!E && sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
		E = true;
		raycast.renderRay(map);
		fov_Vizualisation.clear();
		fov_Vizualisation.append(sf::Vertex(getSprite().getPosition() + sf::Vector2f(10,30), sf::Color(255, 0, 0, 100)));

		for (const auto& intersection : raycast.intersections) {
			fov_Vizualisation.append(sf::Vertex(intersection, sf::Color(255, 150, 30, 100)));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			m_sprite.setTexture(m_texture1); // Changer la texture de la lampe
			m_sprite.move(-5.0f, 0.0f); // Déplacez la lampe vers la gauche
			raycast.attachedEntity->setOrientation(180.0f); // Mettre à jour l'orientation de l'entité
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {	
			m_sprite.setTexture(m_texture); // Changer la texture de la lampe
			m_sprite.move(5.0f, 0.0f); // Déplacez la lampe vers la droite
			raycast.attachedEntity->setOrientation(360.0f); // Mettre à jour l'orientation de l'entité
		}

		if (E && sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
			E = false;
		}
	}
}