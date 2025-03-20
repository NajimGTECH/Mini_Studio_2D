#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>

#include "player.h"
#include "map.h"
#include "entityManager.h"
#include "tileManager.h"

class Game{
private:
	bool m_terminal;
public:
	Game();
	void run();
};

