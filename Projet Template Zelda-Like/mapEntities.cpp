#include "mapEntities.h"

MapEntities::MapEntities(std::string t, float xPos, float yPos, float xScale, float yScale) : type(t), posX(xPos), posY(yPos), scaleX(xScale), scaleY(yScale) {
	sprite.setPosition(xPos, yPos);
	sprite.setScale(xScale, yScale);
}