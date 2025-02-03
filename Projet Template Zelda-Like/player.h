#pragma once

#include "entity.h"
#include "enemy.h"
#include "mapEntities.h"

class Enemy;

class Player : public Entity {
public:
	bool potion = false;
	float potionTimer = 0;
	float baseSpeed = 300;
	bool key1 = false;
	bool lock1opened = false;
	sf::RectangleShape attackArea;
	sf::Vector2f playerPos;
	sf::Vector2f checkpoint = { 75, 75 };

	Player();
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;

	void handleInput(float deltaTime, sf::RenderWindow& window, sf::Sprite wall, std::vector<std::vector<std::unique_ptr<MapEntities>>>& walls, sf::View& view, std::vector<std::unique_ptr<Enemy>>& enemies);
	void potionUpdate(float deltaTime);
};
