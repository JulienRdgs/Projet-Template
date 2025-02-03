#include "patrolling.h"

PatrollingEnemy::PatrollingEnemy(float xPos, float yPos) {
    type = "patrolling";
    sprite.setScale(0.1, 0.1);
    sprite.setPosition({ xPos, yPos });
    posX = xPos;
    posY = yPos;
    /*speedX = 100;
    speedY = 100;*/
    speedX = randomSpeed[rand() % 6];
    speedY = randomSpeed[rand() % 6];
}

void PatrollingEnemy::behavior(float& deltaTime, sf::View& view, std::vector<std::vector<std::unique_ptr<MapEntities>>>& walls, Player& player) {
    if (abs(player.sprite.getPosition().x - sprite.getPosition().x) < view.getSize().x /1.7
        && abs(player.sprite.getPosition().y - sprite.getPosition().y) < view.getSize().y /1.7) {

        sprite.move(speedX * deltaTime, speedY * deltaTime);
        if (player.sprite.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
            sprite.move(-speedX * deltaTime, -speedY * deltaTime);
            player.gotHit = true;
        }

        for (auto& wallz : walls) {
            for (auto& wall : wallz) {
                if (wall->type == "wall") {
                    if (sprite.getGlobalBounds().intersects(wall->sprite.getGlobalBounds())) {
                        /*speedY = -speedY;
                        speedX = -speedX;*/
                        speedX = randomSpeed[rand() % 6];
                        speedY = randomSpeed[rand() % 6];
                    }
                }
            }
        }
    }
}