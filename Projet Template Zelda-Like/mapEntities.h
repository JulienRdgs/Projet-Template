#pragma once

#include "includes.h"

class MapEntities {
public:
	sf::Sprite sprite;
	std::string type;
	float posX;
	float posY;
	float scaleX;
	float scaleY;

	MapEntities(std::string t, float xPos, float yPos, float xScale, float yScale);
};
