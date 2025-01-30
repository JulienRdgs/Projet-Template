#pragma once

#include "interactable.h"

class Key : public Interactable {
public:
	Key();
	Key(float xPos, float yPos);

	void interact(Player& player, std::vector<std::vector<std::unique_ptr<Interactable>>>& mapObjects) override;
};
