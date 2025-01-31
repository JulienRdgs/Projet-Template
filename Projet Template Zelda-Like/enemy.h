#pragma once

#include "player.h"

class Enemy : public Entity {
public:
	std::string type;
	bool state = true;

	Enemy();
	~Enemy();

	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;

	virtual void behavior(float& deltaTime, sf::Sprite& daWall, std::vector<std::vector<std::unique_ptr<MapEntities>>>& walls, Player& player);
};