#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>

#include "entityManager.h"
#include "closet.h"
#include "desk.h"
#include "box.h"
#include "bookShelf.h"
#include "chair.h"
#include "shelf.h"
#include "tileManager.h"
#include "screen.h"

class Game{
private:
	bool m_terminal = false;
public:
	Game();
	void run();

	std::shared_ptr<Lamp>lamp;
};

