#include "player.h"
#include "game.h"
#include "mapEntities.h"

Player::Player() {
    sprite.setScale(0.09f, 0.09f);
    posX = checkpoint.x;
    posY = checkpoint.y;
    speedX = baseSpeed;
    speedY = baseSpeed;

    attackArea.setSize(sf::Vector2f(100.f, 5.f));
    attackArea.setFillColor(sf::Color::Red);
    attackArea.setOrigin(attackArea.getSize().x / 2, attackArea.getSize().y / 2);
}
void Player::update(float deltaTime) {
    posX = sprite.getPosition().x;
    posY = sprite.getPosition().y;
}
void Player::draw(sf::RenderWindow& window) 
{
    window.draw(sprite);
    window.draw(attackArea);
}

void Player::handleInput(float deltaTime, sf::RenderWindow& window, sf::Sprite wall, std::vector<std::vector<std::unique_ptr<MapEntities>>>& walls, sf::View& view, std::vector<std::unique_ptr<Enemy>>& enemies) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f worldMousePos = window.mapPixelToCoords(mousePos);
    sf::Vector2f playerPos(sprite.getPosition().x + (sprite.getLocalBounds().width * sprite.getScale().x) / 2, sprite.getPosition().y + (sprite.getLocalBounds().height * sprite.getScale().y) / 2);

    sf::Vector2f attackDir = worldMousePos - playerPos;
    float angle = std::atan2(attackDir.y, attackDir.x) * 180 / 3.14159f;

    attackArea.setPosition(playerPos);
    attackArea.setRotation(angle);

    float length = 75.f;
    attackArea.setSize(sf::Vector2f(length, 5.f));

    attackArea.setOrigin(attackArea.getSize().x / 10, attackArea.getSize().y / 10);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
    {
        for (auto& enemy : enemies) 
        {
            sf::Vector2f enemyPos = enemy->sprite.getPosition();
            float distance = std::sqrt(std::pow(enemyPos.x - playerPos.x, 2) + std::pow(enemyPos.y - playerPos.y, 2));

            if (distance < length && attackArea.getGlobalBounds().intersects(enemy->sprite.getGlobalBounds())) 
            {
                enemy->takeDamage(10);
            }
        }
    }
    
    //MOUVEMENTS
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        sprite.move(0, speedY * deltaTime);
        view.move(0, speedY * deltaTime);
        for (auto& wallz : walls) {
            for (auto& wall : wallz) {
                if (wall->type == "wall" || (wall->type == "lock" && !key1)) {
                    if (sprite.getGlobalBounds().intersects(wall->sprite.getGlobalBounds())) {
                        sprite.move(0, -speedY * deltaTime);
                        view.move(0, -speedY * deltaTime);
                    }
                }
            }
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        sprite.move(0, -speedY * deltaTime);
        view.move(0, -speedY * deltaTime);
        for (auto& wallz : walls) {
            for (auto& wall : wallz) {
                if (wall->type == "wall" || (wall->type == "lock" && !key1)) {
                    if (sprite.getGlobalBounds().intersects(wall->sprite.getGlobalBounds())) {
                        sprite.move(0, speedY * deltaTime);
                        view.move(0, speedY * deltaTime);
                    }
                }
            }
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        sprite.move(-speedX * deltaTime, 0);
        view.move(-speedX * deltaTime, 0);
        for (auto& wallz : walls) {
            for (auto& wall : wallz) {
                if (wall->type == "wall" || (wall->type == "lock" && !key1)) {
                    if (sprite.getGlobalBounds().intersects(wall->sprite.getGlobalBounds())) {
                        sprite.move(speedX * deltaTime, 0);
                        view.move(speedX * deltaTime, 0);
                    }
                }
            }
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        sprite.move(speedX * deltaTime, 0);
        view.move(speedX * deltaTime, 0);
        for (auto& wallz : walls) {
            for (auto& wall : wallz) {
                if (wall->type == "wall" || (wall->type == "lock" && !key1)) {
                    if (sprite.getGlobalBounds().intersects(wall->sprite.getGlobalBounds())) {
                        sprite.move(-speedX * deltaTime, 0);
                        view.move(-speedX * deltaTime, 0);
                    }
                }
            }
        }
    }
    //INTERAGIR
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        for (auto& wallz : walls) {
            for (auto& wall : wallz) {
                if (wall->type == "checkpoint") {
                    if (sprite.getGlobalBounds().intersects(wall->sprite.getGlobalBounds())) {
                        checkpoint = wall->sprite.getPosition();
                    }
                }
            }
        }
    }

    //OUVRIR PORTE
    if (key1) {
        for (int i = 0; i < walls.size(); i++) {
            for (int y = 0; y < walls[i].size(); y++) {
                if (sprite.getGlobalBounds().intersects(walls[i][y]->sprite.getGlobalBounds())) {
                    if (walls[i][y]->type == "lock") {
                        walls[i].erase(walls[i].begin() + y);
                        lock1opened = true;
                        key1 = false;
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
