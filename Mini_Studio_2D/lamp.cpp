#include "lamp.h"

Lamp::Lamp(int s, int h) : Entity(s, h) {
	fov_Vizualisation = sf::VertexArray(sf::TrianglesFan, 0);
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
		raycast.renderRay();
		fov_Vizualisation.clear();
		fov_Vizualisation.append(sf::Vertex(getShape().getPosition(), sf::Color(255, 0, 0, 100)));

		for (const auto& intersection : raycast.intersections) {
			fov_Vizualisation.append(sf::Vertex(intersection, sf::Color(255, 0, 0, 100)));
		}
		std::cout << raycast.intersections.size() << std::endl << "illuminate" << std::endl;
	}
}
