#include "chaser.h"

ChaserEnemy::ChaserEnemy(float xPos, float yPos) {
	type = "chaser";
	sprite.setScale(0.1, 0.1);
	sprite.setPosition({ xPos, yPos });
	posX = xPos;
	posY = yPos;
	speedX = 100;
	speedY = 100;
}

void ChaserEnemy::behavior(float& deltaTime, sf::Sprite& daWall, std::vector<std::vector<std::unique_ptr<MapEntities>>>& walls, Player& player) {
	playerPosX = player.sprite.getPosition().x + (player.sprite.getLocalBounds().width * player.sprite.getScale().x
		+ player.sprite.getLocalBounds().height * player.sprite.getScale().y
		- sprite.getLocalBounds().width * sprite.getScale().x
		- sprite.getLocalBounds().height * sprite.getScale().y) / 4;
	playerPosY = player.sprite.getPosition().y + (player.sprite.getLocalBounds().width * player.sprite.getScale().x
		+ player.sprite.getLocalBounds().height * player.sprite.getScale().y
		- sprite.getLocalBounds().width * sprite.getScale().x
		- sprite.getLocalBounds().height * sprite.getScale().y) / 4;

	if (posX > playerPosX) {
		sprite.move(-speedX * deltaTime, 0);
	}
	if (posX < playerPosX) {
		sprite.move(speedX * deltaTime, 0);
	}
	if (posY > playerPosY) {
		sprite.move(0, -speedY * deltaTime);
	}
	if (posY < playerPosY) {
		sprite.move(0, speedY * deltaTime);
	}
}