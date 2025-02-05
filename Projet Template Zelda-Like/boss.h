#pragma once

#include "player.h"
#include "mapEntities.h"

class Projectile {
public:
	float speedX = 0;
	float speedY = 0;
	float posX = 0;
	float posY = 0;
	bool state = true;
	sf::Sprite sprite;

	Projectile(float xSpeed, float ySpeed, float xPos, float yPos);
};


class Boss : public Enemy {
public:
	float atk = 10;
	std::vector<float> randomSpeed = { 100, -100, 300, -300, 500, -500 };
	float shootTimer = 0;
	float shootCooldown = 1;
	std::vector<std::unique_ptr<Projectile>> projectiles;
	float projectileInitialPosX = 0;
	float projectileInitialPosY = 0;
	bool hitLimit = false;

	Boss(float xPos, float yPos);

	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window, sf::Sprite& sprite1, sf::Sprite& sprite2, sf::Texture& texture1, sf::Texture& texture2) override;
	void behavior(float& deltaTime, sf::View& view, std::vector<std::vector<std::unique_ptr<MapEntities>>>& walls, Player& player) override;
};
