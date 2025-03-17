#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

enum class MenuState { MAIN, OPTIONS, CONTROLS, SOUND, CUSTOM_LEVELS };

class Menu {
public:
	Menu(float _width, float _height);

	void drawMenu(RenderWindow& window);
	void update(Vector2f mousePos);

	int getselectedIndex() const;

	bool isOptionClicked(Vector2f mousePos);

	void switchToOptions();
	void switchToControls();
	void switchToSound();
	void switchToMain();
	void switchToCustomLevels();

	void stopmenuMusic();

public:

	float volume;

	MenuState menuState;
	Music menuMusic;

	bool startGame = false;

private:
	int selectedIndex;
	Font Menufont;
	vector<Text> menu;
	vector<RectangleShape> menuBox;
};

