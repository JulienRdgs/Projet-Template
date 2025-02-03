#pragma once

#include "player.h"
#include "mapEntities.h"

class Player;

class Enemy : public Entity {
public:
	std::string type;
	bool state = true;
	int health = 30;

	Enemy();
	~Enemy();

	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;

	virtual void behavior(float& deltaTime, sf::View& view, std::vector<std::vector<std::unique_ptr<MapEntities>>>& walls, Player& player);
	virtual void takeDamage(int damage);
};
