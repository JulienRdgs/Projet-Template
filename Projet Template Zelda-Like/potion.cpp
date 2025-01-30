#include "potion.h"

Potion::Potion() {
	type = "potion";
}
Potion::Potion(float xPos, float yPos) {
	type = "potion";
	sprite.setPosition(xPos, yPos);
	posX = xPos;
	posY = yPos;
}

void Potion::interact(Player& player) {
	if (player.sprite.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
		player.potion = true;
		state = false;
	}
}