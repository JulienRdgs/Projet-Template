#pragma once

#include "enemy.h"
#include "map.h"

class PatrollingEnemy : public Enemy {
public:
	bool touchedWall = false;
	std::vector<float> changeX = { -speedX * 0.9f, -speedX };
	std::vector<float> changeY = { -speedY * 0.9f, -speedY };
	std::vector<float> randomSpeed = { 100, -100, 125, -125, 150, -150 };

	PatrollingEnemy(float xPos, float yPos);

	void behavior(float& deltaTime, sf::Sprite& daWall, std::vector<std::vector<std::unique_ptr<MapEntities>>>& walls, Player& player) override;
};