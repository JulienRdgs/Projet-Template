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

void PatrollingEnemy::behavior(float& deltaTime, sf::Sprite& daWall, std::vector<std::vector<std::unique_ptr<MapEntities>>>& walls, Player& player) {
    sprite.move(speedX * deltaTime, speedY * deltaTime);

    for (auto& wallz : walls) {
        for (auto& wall : wallz) {
            if (wall->type == "wall") {
                if (sprite.getGlobalBounds().intersects(wall->sprite.getGlobalBounds())) {
                    touchedWall = true;
                }
            }
        }
    }
    if (touchedWall) {
        /*speedY = changeY[rand() % 2];
        speedX = changeX[rand() % 2];*/
        speedY = -speedY;
        speedX = -speedX;
    }
    touchedWall = false;

    /*if (sprite.getGlobalBounds().intersects(daWall.getGlobalBounds())) {
        speedY = -speedY;
        speedX = -speedX;
    }*/
}