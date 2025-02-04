
//#include "PNJ.h"
//
//PNJ::PNJ() {
//	type = "pnj";
//}
//PNJ::PNJ(std::string pnj, float xPos, float yPos) {
//	type = "pnj";
//	sprite.setPosition(xPos, yPos);
//	posX = xPos;
//	posY = yPos;
//}
//
//void PNJ::interact(Player& player, std::vector<std::unique_ptr<Interactable>>& mapObjects) {
//	if (player.sprite.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
//		player.pnj = true;
//	}
//}