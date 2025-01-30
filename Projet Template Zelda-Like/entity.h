#pragma once

#include "includes.h"

class Entity {
public:
	sf::Sprite sprite;
	float posX = 0;
	float posY = 0;
	float speedX = 0;
	float speedY = 0;

	Entity();
	virtual void update(float deltaTime) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
};