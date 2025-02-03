#pragma once

#include "interactable.h"

class Key : public Interactable {
public:
	std::string keyNumber = "null";

	Key();
	Key(std::string keyNumber, float xPos, float yPos);

	void interact(Player& player, std::vector<std::unique_ptr<Interactable>>& mapObjects) override;
};
