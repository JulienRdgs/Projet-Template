#pragma once

#include "includes.h"
#include "player.h"
#include "chaser.h"
#include "patrolling.h"
#include "potion.h"
#include "key.h"
#include "map.h"


class Game {
public:
	sf::RenderWindow window;
	Player player;
	Map theMap;
	std::vector<std::unique_ptr<Enemy>> enemies;
	std::vector<std::unique_ptr<Interactable>> objects;
	sf::Clock Clock;
	float deltaTime = 0;
	bool playing = true;
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
	sf::Text gameOverText;
	sf::Text retryText;

	Game();

	void loadTextures();
	void setupSpawns();
	void gameLoop();
	void pollEvent();
	void updateAll();
	void drawAll();
	void reset();
	void run();
};