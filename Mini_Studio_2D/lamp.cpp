#include "lamp.h"

Lamp::Lamp(int s, int h) : Entity(s, h) {
	m_shape.setPosition(500, 200);
	fov_Vizualisation = sf::VertexArray(sf::TriangleFan, 0);
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
	if (countE < 1 && sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
		countE++;
		raycast.renderRay();
		fov_Vizualisation.clear();

		for (const auto& intersection : raycast.intersections) {
			fov_Vizualisation.append(sf::Vertex(intersection, sf::Color(255, 150, 30, 100)));
		}
	}
	if (countE == 1 && sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
		// idk ask colleages
		countE = 0;
	}
}