
#include "key.h"

Key::Key() {
	type = "key";
}
Key::Key(float xPos, float yPos) {
	type = "key";
	sprite.setPosition(xPos, yPos);
	posX = xPos;
	posY = yPos;
}

void Key::interact(Player& player, std::vector<std::vector<std::unique_ptr<Interactable>>>& mapObjects) {
	if (player.sprite.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
		player.key = true;
		state = false;
	}
}
