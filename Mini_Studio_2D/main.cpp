#include <iostream>

#include <SFML/Graphics.hpp>

#include "game.h"

int main() {
	srand(time(0));
	Game game;
	game.run();
    return 0;
}