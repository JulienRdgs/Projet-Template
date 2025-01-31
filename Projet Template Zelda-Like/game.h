#pragma once

#include "includes.h"
#include "player.h"
#include "chaser.h"
#include "patrolling.h"
#include "potion.h"
#include "key.h"
#include "map.h"


class Game {
private:
	float volume;
public:
	bool start = true;
	sf::RenderWindow window;
	sf::View view;
	Player player;
	Map theMap;
	sf::Clock Clock;
	float deltaTime = 0;
	bool playing = false;
	bool win = false;
	bool gameOver = false;

	sf::Texture playerTexture;
	sf::Texture chaserTexture;
	sf::Texture patrollingTexture;
	sf::Texture potionTexture;
	sf::Texture keyTexture;
	sf::Texture wallTexture;
	sf::Texture floorTexture;
	sf::Texture lockTexture;

	sf::Sprite keyIcone;
	sf::Sprite wallSprite;
	sf::Sprite floorSprite;
	sf::Sprite lockSprite;

	sf::Font baseFont;
	sf::Text winText;
	sf::Text menuText;
	sf::Text volumeText;
	sf::Text gameOverText;
	sf::Text retryText;

	Game(std::vector<sf::VideoMode> modes);

	void loadTextures();
	//void setupSpawns();
	void gameLoop();
	void pollEvent();
	void showMenu();
	void loadFont();
	void showOptionsMenu();
	void updateAll();
	void drawAll();
	void reset();
	void run();
};