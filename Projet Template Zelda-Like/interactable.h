#pragma once

#include "player.h"

class Interactable {
public:
	float posX;
	float posY;
	bool state = true;
	std::string type;
	sf::Sprite sprite;

	Interactable();

	virtual void interact(Player& player, std::vector<std::unique_ptr<Interactable>>& mapObjects) = 0;
	//void destroy(std::vector<Interactable>& objects);
};
