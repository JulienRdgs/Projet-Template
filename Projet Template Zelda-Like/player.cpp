#include "player.h"
#include "game.h"
#include "mapEntities.h"

Player::Player(float xPos, float yPos) {
    sprite.setScale(0.09f, 0.09f);
    sprite.setPosition({ xPos, yPos });
    posX = xPos;
    posY = yPos;
    speedX = baseSpeed;
    speedY = baseSpeed;
}
void Player::update(float deltaTime) {
    posX = sprite.getPosition().x;
    posY = sprite.getPosition().y;
}
void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}
void Player::handleInput(float deltaTime, sf::RenderWindow& window, sf::Sprite wall, std::vector<std::vector<std::unique_ptr<MapEntities>>>& walls) {
    //MOUVEMENTS
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        sprite.move(0, speedY * deltaTime);
        /*if (sprite.getGlobalBounds().intersects(wall.getGlobalBounds())) {
            sprite.move(0, -speedY * deltaTime);
        }*/
        for (auto& wallz : walls) {
            for (auto& wall : wallz) {
                if (wall->type == "wall" || (wall->type == "lock" && !key)) {
                    if (sprite.getGlobalBounds().intersects(wall->sprite.getGlobalBounds())) {
                        sprite.move(0, -speedY * deltaTime);
                    }
                }
            }
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        sprite.move(0, -speedY * deltaTime);
        /*if (sprite.getGlobalBounds().intersects(wall.getGlobalBounds())) {
            sprite.move(0, speedY * deltaTime);
        }*/
        for (auto& wallz : walls) {
            for (auto& wall : wallz) {
                if (wall->type == "wall" || (wall->type == "lock" && !key)) {
                    if (sprite.getGlobalBounds().intersects(wall->sprite.getGlobalBounds())) {
                        sprite.move(0, speedY * deltaTime);
                    }
                }
            }
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        sprite.move(-speedX * deltaTime, 0);
        /*if (sprite.getGlobalBounds().intersects(wall.getGlobalBounds())) {
            sprite.move(speedX * deltaTime, 0);
        }*/
        for (auto& wallz : walls) {
            for (auto& wall : wallz) {
                if (wall->type == "wall" || (wall->type == "lock" && !key)) {
                    if (sprite.getGlobalBounds().intersects(wall->sprite.getGlobalBounds())) {
                        sprite.move(speedX * deltaTime, 0);
                    }
                }
            }
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        sprite.move(speedX * deltaTime, 0);
        /*if (sprite.getGlobalBounds().intersects(wall.getGlobalBounds())) {
            sprite.move(-speedX * deltaTime, 0);
        }*/
        for (auto& wallz : walls) {
            for (auto& wall : wallz) {
                if (wall->type == "wall" || (wall->type == "lock" && !key)) {
                    if (sprite.getGlobalBounds().intersects(wall->sprite.getGlobalBounds())) {
                        sprite.move(-speedX * deltaTime, 0);
                    }
                }
            }
        }
    }
}

void Player::potionUpdate(float deltaTime) {
    if (potion) {
        sprite.setColor(sf::Color(24, 202, 237));
        speedX = baseSpeed * 1.75f;
        speedY = baseSpeed * 1.75f;
        if (potionTimer >= 5) potion = false;
    }
    else {
        sprite.setColor(sf::Color::White);
        potionTimer = 0;
        speedX = baseSpeed;
        speedY = baseSpeed;
    }
}