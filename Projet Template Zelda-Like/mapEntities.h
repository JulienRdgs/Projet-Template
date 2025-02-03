#pragma once

#include "includes.h"

class MapEntities {
public:
	sf::Sprite sprite;
	std::string type;
	std::string lockNumber = "null";
	float posX;
	float posY;
	float scaleX;
	float scaleY;

	MapEntities(std::string t, float xPos, float yPos, float xScale, float yScale);
	MapEntities(std::string t, std::string lockNumber, float xPos, float yPos, float xScale, float yScale);
};
