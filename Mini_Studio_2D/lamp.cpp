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

//// Convertir un sf::Vector2f en Point64 pour ClipperLib
//Clipper2Lib::Point64 Lamp::toPoint64(const sf::Vector2f& point) {
//	return Clipper2Lib::Point64(static_cast<int>(point.x * 100), static_cast<int>(point.y * 100));
//}
//
//// Convertir un Point64 en sf::Vector2f pour SFML
//sf::Vector2f Lamp::toSfVector2f(const Clipper2Lib::Point64& point) {
//	return sf::Vector2f(point.x / 100.0f, point.y / 100.0f);
//}

void Lamp::update(float deltaTime) {

	//sf::RectangleShape shadowOverlay(sf::Vector2f(1920, 1080));
	//shadowOverlay.setFillColor(sf::Color(0, 0, 0, 255));

	//// ClipperLib: Calcul de l'effet de lampe
	//Clipper2Lib::Paths64 shadow, lightCone, result;
	//Clipper2Lib::Path64 shadowRect = { toPoint64({0, 0}), toPoint64({1920, 0}), toPoint64({1920, 1080}), toPoint64({0, 1080}) };
	//Clipper2Lib::Path64 lightArea;
	//for (const auto& point : raycast.intersections) {
	//	lightArea.push_back(toPoint64(point));
	//}
	//lightArea.insert(lightArea.begin(), toPoint64(getSprite().getPosition()));

	//shadow.push_back(shadowRect);
	//lightCone.push_back(lightArea);

	//Clipper2Lib::Clipper64 clipper;
	//clipper.AddSubject(shadow);
	//clipper.AddClip(lightCone);
	//clipper.Execute(Clipper2Lib::ClipType::Difference, Clipper2Lib::FillRule::NonZero, result);

	//// Dessin de l'ombre
	//sf::VertexArray shadowShape(sf::TriangleFan);
	//for (const auto& poly : result) {
	//	for (const auto& point : poly) {
	//		shadowShape.append(sf::Vertex(toSfVector2f(point), sf::Color(0, 0, 0, 255)));
	//	}
	//}
	
	if (dynamic_cast<Player*>(m_owner)->getE()) {
		illuminate();
	}
	for (const auto& intersection : raycast.intersections) {
		fov_Vizualisation.append(sf::Vertex(intersection, sf::Color(255, 150, 30, 0)));
	}
	if (dynamic_cast<Player*>(m_owner)->getWalkSide()) {
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
		/*window.draw(m_shadowShape);*/

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
		fov_Vizualisation.append(sf::Vertex(getSprite().getPosition() + sf::Vector2f(10, 30), sf::Color(255, 0, 0, 0)));
	}

}


void Lamp::anim(float deltaTime){}



////////////////////////////////////// clipper pour effet lampe et permettre la transparence du raycast foireux //////////////////////////////////////////////////