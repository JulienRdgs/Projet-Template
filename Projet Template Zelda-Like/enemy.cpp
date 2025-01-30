#include "enemy.h"
#include "chaser.h"
#include "patrolling.h"

Enemy::Enemy() {}

Enemy::~Enemy() {}

void Enemy::update(float deltaTime) {
    posX = sprite.getPosition().x;
    posY = sprite.getPosition().y;
}
void Enemy::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Enemy::behavior(float& deltaTime, sf::Sprite& daWall, std::vector<std::vector<std::unique_ptr<MapEntities>>>& walls, Player& player) {}