#pragma once

#include "mapEntities.h"
#include "chaser.h"
#include "interactable.h"
#include "player.h"

class Map {
public:
	std::ifstream mapFile;
	std::vector<std::vector<std::unique_ptr<MapEntities>>> mapObjects;
	std::vector<std::unique_ptr<Enemy>> enemies;
	std::vector<std::shared_ptr<Interactable>> objects;

	std::string line;

	Map();

	void loadMap(Player& player);
};