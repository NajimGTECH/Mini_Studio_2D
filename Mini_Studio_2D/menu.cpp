#include "menu.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;


Menu::Menu(float _width, float _height) : selectedIndex(0), menuState(MenuState::MAIN) {
	if (!Menufont.loadFromFile("Assets/TexteMenu/SolarPunk.otf")) {
		cout << "Error loading font" << endl;
	}
	if (!menuMusic.openFromFile("Assets/AudioMenu/Menumusic.mp3")) {
		cout << "Erreur chargement musique" << endl;
	}
	else {
		menuMusic.setLoop(true);
		volume = 30;
		menuMusic.setVolume(volume);
		menuMusic.play();
	}

	//===============Menu principal===================
	vector<string> mainMenuItems = { "Play", "Options", "Exit" };
	for (int i = 0; i < mainMenuItems.size(); i++) {
		Text text;
		text.setFont(Menufont);
		text.setString(mainMenuItems[i]);
		text.setCharacterSize(40);
		text.setFillColor(Color::White);

		float posX = 960 - 125;
		float posY = 300 + (i * 100);

		RectangleShape box(Vector2f(250, 60));
		box.setPosition(Vector2f(posX, posY));
		box.setFillColor(Color::Black);
		box.setOutlineColor(Color::White);
		box.setOutlineThickness(2);

		FloatRect textBounds = text.getLocalBounds();
		text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
		text.setPosition(posX + box.getSize().x / 2.0f, posY + box.getSize().y / 2.0f);

		menu.push_back(text);
		menuBox.push_back(box);
	}
}

void Menu::update(Vector2f mousePos) {
	selectedIndex = -1;

	for (int i = 0; i < menuBox.size(); i++) {
		if (menuBox[i].getGlobalBounds().contains(mousePos)) {
			selectedIndex = i;
			menuBox[i].setFillColor(Color(255, 0, 0, 150));
			menu[i].setFillColor(Color::White);
		}
		else {
			menuBox[i].setFillColor(Color::Black);
			menu[i].setFillColor(Color::White);
		}
	}
}


bool Menu::isOptionClicked(Vector2f mousePos) {
	if (selectedIndex != -1 && menuBox[selectedIndex].getGlobalBounds().contains(mousePos)) {
		return true;
	}
	return false;
}


void Menu::switchToOptions() {
	menu.clear();
	menuBox.clear();
	selectedIndex = -1;
	menuState = MenuState::OPTIONS;

	vector<string> optionsItems = { "Sound & Music", "Controls", "Back" };
	for (int i = 0; i < optionsItems.size(); i++) {
		float posX = (i == 0) ? 300 : (i == 1) ? 1300 : 80;
		float posY = (i == 2) ? 790 : 300;

		RectangleShape box(Vector2f(300, 80));
		box.setPosition(posX, posY);
		box.setFillColor(Color::Black);
		box.setOutlineColor(Color::White);
		box.setOutlineThickness(2);

		Text text;
		text.setFont(Menufont);
		text.setString(optionsItems[i]);
		text.setCharacterSize(40);
		text.setFillColor(Color::White);


		FloatRect textBounds = text.getLocalBounds();
		text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
		text.setPosition(posX + box.getSize().x / 2.0f, posY + box.getSize().y / 2.0f);

		menu.push_back(text);
		menuBox.push_back(box);
	}
}


void Menu::switchToControls() {
	menu.clear();
	menuBox.clear();
	selectedIndex = -1;
	menuState = MenuState::CONTROLS;

	vector<string> controlsText = {
		"Movement - Z/Q/S/D",
		"Left click - Smite",
		"Space - Bomb (need to be unlocked)"
	};

	for (int i = 0; i < controlsText.size(); i++) {
		Text text;
		text.setFont(Menufont);
		text.setString(controlsText[i]);
		text.setCharacterSize(40);
		text.setFillColor(Color::White);
		FloatRect textBounds = text.getLocalBounds();
		text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
		text.setPosition(960, 200 + i * 60);

		menu.push_back(text);
	}

	float backPosX = 80;
	float backPosY = 790;
	RectangleShape backBox(Vector2f(200, 60));
	backBox.setPosition(backPosX, backPosY);
	backBox.setFillColor(Color::Black);
	backBox.setOutlineColor(Color::White);
	backBox.setOutlineThickness(2);

	Text backText;
	backText.setFont(Menufont);
	backText.setString("Back");
	backText.setCharacterSize(40);
	backText.setFillColor(Color::White);

	FloatRect textBounds = backText.getLocalBounds();
	backText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
	backText.setPosition(backPosX + backBox.getSize().x / 2.0f, backPosY + backBox.getSize().y / 2.0f);

	menu.push_back(backText);
	menuBox.push_back(backBox);
}

void Menu::switchToSound() {
	menu.clear();
	menuBox.clear();
	selectedIndex = -1;
	menuState = MenuState::SOUND;

	float centerX = 960;
	float centerY = 400;

	Text volumeText;
	volumeText.setFont(Menufont);
	volumeText.setString("Volume");
	volumeText.setCharacterSize(40);
	volumeText.setFillColor(Color::White);

	FloatRect volumeBounds = volumeText.getLocalBounds();
	volumeText.setOrigin(volumeBounds.width / 2.0f, volumeBounds.height / 2.0f);
	volumeText.setPosition(centerX, centerY - 100);

	Text volumeValueText;
	volumeValueText.setFont(Menufont);
	volumeValueText.setString(to_string(static_cast<int>(menuMusic.getVolume())));
	volumeValueText.setCharacterSize(40);
	volumeValueText.setFillColor(Color::White);

	FloatRect valueBounds = volumeValueText.getLocalBounds();
	volumeValueText.setOrigin(valueBounds.width / 2.0f, valueBounds.height / 2.0f);
	volumeValueText.setPosition(centerX, centerY);

	// ➖ Bouton "-" (baisser le son)
	RectangleShape minusBox(Vector2f(80, 80));
	minusBox.setPosition(centerX - 150, centerY);
	minusBox.setFillColor(Color::Black);
	minusBox.setOutlineColor(Color::White);
	minusBox.setOutlineThickness(2);

	Text minusText;
	minusText.setFont(Menufont);
	minusText.setString("-");
	minusText.setCharacterSize(40);
	minusText.setFillColor(Color::White);

	FloatRect minusBounds = minusText.getLocalBounds();
	minusText.setOrigin(minusBounds.width / 2.0f, minusBounds.height / 2.0f);
	minusText.setPosition(centerX - 150 + minusBox.getSize().x / 2.0f, centerY + minusBox.getSize().y / 4.0f);

	// ➕ Bouton "+" (augmenter le son)
	RectangleShape plusBox(Vector2f(80, 80));
	plusBox.setPosition(centerX + 70, centerY);
	plusBox.setFillColor(Color::Black);
	plusBox.setOutlineColor(Color::White);
	plusBox.setOutlineThickness(2);

	Text plusText;
	plusText.setFont(Menufont);
	plusText.setString("+");
	plusText.setCharacterSize(40);
	plusText.setFillColor(Color::White);

	FloatRect plusBounds = plusText.getLocalBounds();
	plusText.setOrigin(plusBounds.width / 2.0f, plusBounds.height / 2.0f);
	plusText.setPosition(centerX + 70 + plusBox.getSize().x / 2.0f, centerY + plusBox.getSize().y / 4.0f);

	// 🔙 Bouton "Back"
	RectangleShape backBox(Vector2f(200, 60));
	backBox.setPosition(80, 790);
	backBox.setFillColor(Color::Black);
	backBox.setOutlineColor(Color::White);
	backBox.setOutlineThickness(2);

	Text backText;
	backText.setFont(Menufont);
	backText.setString("Back");
	backText.setCharacterSize(40);
	backText.setFillColor(Color::White);

	FloatRect backBounds = backText.getLocalBounds();
	backText.setOrigin(backBounds.width / 2.0f, backBounds.height / 2.0f);
	backText.setPosition(80 + backBox.getSize().x / 2.0f, 790 + backBox.getSize().y / 3.0f);

	menu.push_back(volumeText);
	menu.push_back(volumeValueText);
	menu.push_back(minusText);
	menu.push_back(plusText);
	menu.push_back(backText);

	menuBox.push_back(minusBox);
	menuBox.push_back(plusBox);
	menuBox.push_back(backBox);
}




void Menu::switchToMain() {
	menu.clear();
	menuBox.clear();
	selectedIndex = -1;
	menuState = MenuState::MAIN;

	vector<string> mainMenuItems = { "Play", "Options", "Exit" };
	for (int i = 0; i < mainMenuItems.size(); i++) {
		Text text;
		text.setFont(Menufont);
		text.setString(mainMenuItems[i]);
		text.setCharacterSize(40);
		text.setFillColor(Color::White);

		float posX = 960 - 125;
		float posY = 300 + (i * 100);

		RectangleShape box(Vector2f(250, 60));
		box.setPosition(Vector2f(posX, posY));
		box.setFillColor(Color::Black);
		box.setOutlineColor(Color::White);
		box.setOutlineThickness(2);

		FloatRect textBounds = text.getLocalBounds();
		text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
		text.setPosition(posX + box.getSize().x / 2.0f, posY + box.getSize().y / 2.0f);

		menu.push_back(text);
		menuBox.push_back(box);
	}
}

void Menu::stopmenuMusic() {
	menuMusic.stop();
}

void Menu::drawMenu(RenderWindow& window) {
	for (int i = 0; i < menuBox.size(); i++) {
		window.draw(menuBox[i]);
	}
	for (int i = 0; i < menu.size(); i++) {
		window.draw(menu[i]);
	}
}

int Menu::getselectedIndex() const {
	return selectedIndex;
}