#pragma once

#include "interactable.h"

class Potion : public Interactable {
public:

	Potion();
	Potion(float xPos, float yPos);

	void interact(Player& player) override;
};
