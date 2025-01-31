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

void Potion::interact(Player& player, std::vector<std::unique_ptr<Interactable>>& mapObjects) {
	if (player.sprite.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
		player.potion = true;
		state = false;
		/*for (auto& objz : mapObjects) {
			auto it = std::find(objz.begin(), objz.end(), this);
			if (it != objz.end()) objz.erase(it);
		}*/
	}
}