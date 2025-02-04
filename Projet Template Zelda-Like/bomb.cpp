#include "potion.h"

Bomb::Bomb() {
	type = "bomb";
}
Bomb::Bomb(float xPos, float yPos) {
	type = "bomb";
	sprite.setPosition(xPos, yPos);
	posX = xPos;
	posY = yPos;
}

bool Bomb::interact(sf::Sprite& playerSprite, std::vector<std::shared_ptr<Interactable>>& mapObjects, std::vector<std::shared_ptr<Interactable>>& inventaire) {
	if (playerSprite.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
		inventaire.emplace_back(std::make_shared<Bomb>());
		state = false;
		return true;
	}
	else { return false; }
}