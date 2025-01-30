#pragma once

#include "entity.h"
#include "mapEntities.h"

class Player : public Entity {
public:
	bool potion = false;
	float potionTimer = 0;
	float baseSpeed = 300;
	bool key = false;
	sf::Vector2f playerPos;

	Player(float posX, float posY);
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;

	void handleInput(float deltaTime, sf::RenderWindow& window, sf::Sprite wall, std::vector<std::vector<std::unique_ptr<MapEntities>>>& walls);
	void potionUpdate(float deltaTime);
};