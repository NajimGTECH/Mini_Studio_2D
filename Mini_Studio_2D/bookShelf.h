#pragma once
#include "entity.h"
#include "player.h"

class BookShelf : public Entity{
public:
	BookShelf(int s, int h, Map& map);
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	void Push(Player& player);
};

