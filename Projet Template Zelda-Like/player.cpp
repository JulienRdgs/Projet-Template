#include "player.h"
#include "game.h"
#include "mapEntities.h"

Player::Player() {
    sprite.setScale(0.09f, 0.09f);
    posX = checkpoint.x;
    posY = checkpoint.y;
    speedX = baseSpeed;
    speedY = baseSpeed;

    sword.setSize(sf::Vector2f(60.f, 10.f));
    sword.setFillColor(sf::Color::Yellow);
    sword.setOrigin(0, sword.getSize().y / 2);

    attackHitbox.setSize(sf::Vector2f(100.f, 60.f));
    attackHitbox.setFillColor(sf::Color(255, 0, 0, 150));
    attackHitbox.setOrigin(attackHitbox.getSize().x / 15, attackHitbox.getSize().y / 10);
}
void Player::update(float deltaTime) {
    if (isAttacking) {
        attackTimer -= deltaTime;
        if (attackTimer <= 0) {
            isAttacking = false;
        }
    }

    sword.setPosition(sprite.getPosition() + swordOffset);
    attackHitbox.setPosition(sprite.getPosition() + attackOffset);

    //AU CAS OU
    posX = sprite.getPosition().x;
    posY = sprite.getPosition().y;
    //POTION UPDATE
    potionTimer += deltaTime;
    if (potion) {
        //sprite.setColor(sf::Color(24, 202, 237));  //TROUVER AUTRE CHOSE A AFFICHER QUAND POTION ACTIVE
        speedX = baseSpeed * 5.75f;
        speedY = baseSpeed * 5.75f;
        if (potionTimer >= 5) potion = false;
    }
    else {
        //sprite.setColor(sf::Color::White);
        potionTimer = 0;
        speedX = baseSpeed;
        speedY = baseSpeed;
    }
    //HIT DETECTION
    if (gotHit) {
        sprite.setColor(sf::Color::Red);
        invincibleTimer += deltaTime;
        if (invincibleTimer > invincibleLimit) gotHit = false;
    }
    else {
        sprite.setColor(sf::Color::White);
        invincibleTimer = 0;
    }
}
void Player::draw(sf::RenderWindow& window) 
{
    window.draw(sprite);
    window.draw(sword);
    if (isAttacking) {
        window.draw(attackHitbox);
    }
}

void Player::handleInput(float deltaTime, sf::RenderWindow& window, sf::Sprite wall, std::vector<std::vector<std::unique_ptr<MapEntities>>>& walls, sf::View& view, std::vector<std::unique_ptr<Enemy>>& enemies) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isAttacking) {
        isAttacking = true;
        attackTimer = attackDuration;

        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        sf::Vector2f playerPos = sprite.getPosition();
        sf::Vector2f direction = mousePos - playerPos;

        if (std::abs(direction.x) > std::abs(direction.y)) {
            if (direction.x > 0) {
                attackOffset = sf::Vector2f(55.f, 0.f);
                swordOffset = sf::Vector2f(55.f, 0.f);
                sword.setRotation(0);
                attackHitbox.setSize(sf::Vector2f(90.f, 40.f));
            }
            else {
                attackOffset = sf::Vector2f(-90.f, 0.f);
                swordOffset = sf::Vector2f(0.f, 0.f);
                sword.setRotation(180);
                attackHitbox.setSize(sf::Vector2f(90.f, 40.f));
            }
        }
        else {
            if (direction.y > 0) {
                attackOffset = sf::Vector2f(0.f, 55.f);
                swordOffset = sf::Vector2f(0.f, 55.f);
                sword.setRotation(90);
                attackHitbox.setSize(sf::Vector2f(40.f, 90.f));
            }
            else {
                attackOffset = sf::Vector2f(0.f, -90.f);
                swordOffset = sf::Vector2f(0.f, 0.f);
                sword.setRotation(-90);
                attackHitbox.setSize(sf::Vector2f(40.f, 90.f));
            }
        }

        for (auto& enemy : enemies) {
            if (attackHitbox.getGlobalBounds().intersects(enemy->sprite.getGlobalBounds())) {
                enemy->takeDamage(20);
            }
        }
    }

    //MOUVEMENTS
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        sprite.move(0, speedY * deltaTime);
        view.move(0, speedY * deltaTime);
        for (auto& wallz : walls) {
            for (auto& wall : wallz) {
                if (wall->type == "wall" || (wall->type == "lock" && !key1) || wall->type == "pnj") {
                    if (sprite.getGlobalBounds().intersects(wall->sprite.getGlobalBounds())) {
                        sprite.move(0, -speedY * deltaTime);
                        view.move(0, -speedY * deltaTime);
                        if (wall->type == "pnj")
                        {
                            pnj = true;
                        }
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
                if (wall->type == "wall" || (wall->type == "lock" && !key1) || wall->type == "pnj") {
                    if (sprite.getGlobalBounds().intersects(wall->sprite.getGlobalBounds())) {
                        sprite.move(0, speedY * deltaTime);
                        view.move(0, speedY * deltaTime);
                        if (wall->type == "pnj")
                        {
                            pnj = true;
                        }
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
                if (wall->type == "wall" || (wall->type == "lock" && !key1) || wall->type == "pnj") {
                    if (sprite.getGlobalBounds().intersects(wall->sprite.getGlobalBounds())) {
                        sprite.move(speedX * deltaTime, 0);
                        view.move(speedX * deltaTime, 0);
                        if (wall->type == "pnj")
                        {
                            pnj = true;
                        }
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
                if (wall->type == "wall" || (wall->type == "lock" && !key1) || wall->type == "pnj") {
                    if (sprite.getGlobalBounds().intersects(wall->sprite.getGlobalBounds())) {
                        sprite.move(-speedX * deltaTime, 0);
                        view.move(-speedX * deltaTime, 0);
                        if (wall->type == "pnj")
                        {
                            pnj = true;
                        }
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
                        checkpointUpdate();
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

void Player::checkpointUpdate() {
    checkpointHp = hp;
    checkpointKey1 = key1;
    checkpointLock1opened = lock1opened;
}

void Player::checkpointResetPlayer() {
    hp = checkpointHp;
    key1 = checkpointKey1;
    //key1 = false;
    lock1opened = checkpointLock1opened;
    sprite.setPosition(checkpoint);
    potion = false;
    pnjMove = false;
}
