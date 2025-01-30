
#include "key.h"

Key::Key() {
	type = "key";
}
Key::Key(float xPos, float yPos) {
	type = "potion";
	sprite.setPosition(xPos, yPos);
	posX = xPos;
	posY = yPos;
}

void Key::interact(Player& player) {
	if (player.sprite.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
		player.key = true;
		state = false;
	}
}
