#include "enemy.h"
#include "chaser.h"
#include "patrolling.h"

Enemy::Enemy() {}

Enemy::~Enemy() {}

void Enemy::update(float deltaTime) {
    posX = sprite.getPosition().x;
    posY = sprite.getPosition().y;
}
void Enemy::draw(sf::RenderWindow& window, sf::Sprite& sprite1, sf::Sprite& sprite2, sf::Texture& texture1, sf::Texture& texture2) {
    if (type == "chaser") sprite.setTexture(texture1);
    else if (type == "patrolling") sprite.setTexture(texture2);
    window.draw(sprite);
}

void Enemy::behavior(float& deltaTime, sf::View& view, std::vector<std::vector<std::unique_ptr<MapEntities>>>& walls, Player& player) {}

void Enemy::takeDamage(int damage) 
{
    health -= damage;
    if (health <= 0)
    {
        state = false;
    }
}
