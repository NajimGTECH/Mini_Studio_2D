#pragma once

#include "map.h"

class TileManager
{
public:

	TileManager();

	void applyTileSet(Map& map);

private:
	sf::Texture m_tileSet;
};

