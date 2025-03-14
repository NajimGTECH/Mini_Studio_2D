#include "lamp.h"

Lamp::Lamp(int s, int h) : Entity(s, h) {
	m_shape.setPosition(500, 400);
	fov_Vizualisation = sf::VertexArray(sf::TriangleFan, 0);
	raycast.attachedEntity = this;

}

void Lamp::update(float deltaTime) {
	//radiusVision.setPosition(shape.getPosition());
	illuminate();
	std::cout << "update" << std::endl;
}

void Lamp::draw(sf::RenderWindow& window) {
	window.draw(m_shape);
	window.draw(fov_Vizualisation);
}

void Lamp::illuminate() {
	int countE = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
		/*if (countE == 0) {
			countE++;*/
		raycast.renderRay();
		fov_Vizualisation.clear();

		for (const auto& intersection : raycast.intersections) {
			fov_Vizualisation.append(sf::Vertex(intersection, sf::Color(255, 150, 30, 100)));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			m_shape.move(-2.0f, 0.0f); // Déplacez la lampe vers la gauche
			raycast.attachedEntity->setOrientation(180.0f); // Mettre à jour l'orientation de l'entité
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			m_shape.move(2.0f, 0.0f); // Déplacez la lampe vers la droite
			raycast.attachedEntity->setOrientation(360.0f); // Mettre à jour l'orientation de l'entité
		}
		/*}*/
		/*else {
			countE = 0;
		}*/
	}
}