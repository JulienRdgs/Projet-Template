#pragma once

#include "entity.h"
#include "enemy.h"
#include "mapEntities.h"

class Enemy;

class Player : public Entity {
public:
	float hp = 100;
	bool potion = false;
	float potionTimer = 0;
	float baseSpeed = 300;
	bool key1 = false;
	bool lock1opened = false;
	sf::RectangleShape attackArea;
	sf::Vector2f playerPos;
	sf::Vector2f checkpoint = { 75, 75 };
	bool gotHit = false;
	float invincibleTimer = 0;
	float invincibleLimit = 3;

	Player();
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;

	void handleInput(float deltaTime, sf::RenderWindow& window, sf::Sprite wall, std::vector<std::vector<std::unique_ptr<MapEntities>>>& walls,
		sf::View& view, std::vector<std::unique_ptr<Enemy>>& enemies);

	bool checkpointHp = 100;
	bool checkpointKey1 = false;
	bool checkpointLock1opened = false;
	void checkpointUpdate();
	void checkpointResetPlayer();
};
