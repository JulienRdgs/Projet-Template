#pragma once

#include "includes.h"

class Interactable {
public:
	std::string keyNumber = "null";
	float posX;
	float posY;
	bool state = true;
	std::string type;
	sf::Sprite sprite;

	Interactable();

	virtual bool interact(sf::Sprite& playerSprite, std::vector<std::shared_ptr<Interactable>>& mapObjects,std::vector<std::shared_ptr<Interactable>>& inventaire) = 0;
	//void destroy(std::vector<Interactable>& objects);
};
