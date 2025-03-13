#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>

#include "player.h"
#include "map.h"
#include "entityManager.h"

class Game{
private:
	bool m_terminal = false;

public:
	Game();
	void run();
};

