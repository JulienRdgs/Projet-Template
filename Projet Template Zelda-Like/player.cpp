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
    //CHECK INVENTAIRE
    bombCount = 0;
    key1 = false;
    for (auto& obj : inventaire) {
        if (obj->type == "key") {
            if (obj->keyNumber == "key1") key1 = true;
        }
        if (obj->type == "bomb") bombCount++;
    }
    //BOMBS
    bombThrowTimer += deltaTime;
    for (auto& bomb : moovingBomb) {
        bomb->sprite.move(bomb->speedX * deltaTime, bomb->speedY * deltaTime);
    }
}
void Player::draw(sf::RenderWindow& window, sf::Sprite& sprite1, sf::Sprite& sprite2, sf::Texture& texture1, sf::Texture& texture2) {

    if (key1) window.draw(sprite1);
    window.draw(sprite2);
    window.draw(sprite);
    window.draw(sword);
    bombText.setString(std::to_string(bombCount));
    bombText.setPosition(sprite2.getPosition().x + (sprite2.getLocalBounds().width * sprite2.getScale().x),
        sprite2.getPosition().y + (sprite2.getLocalBounds().height * sprite2.getScale().y) / 2 - bombText.getCharacterSize() / 2);
    if (!moovingBomb.empty()) {
        for (auto& bomb : moovingBomb) {
            bomb->sprite.setTexture(texture1);
            window.draw(bomb->sprite);
        }
    }
    window.draw(bombText);
    if (isAttacking) {
        window.draw(attackHitbox);
    }
}

void Player::handleInput(float deltaTime, sf::RenderWindow& window, sf::Sprite wall,
    std::vector<std::vector<std::unique_ptr<MapEntities>>>& walls, sf::View& view, std::vector<std::unique_ptr<Enemy>>& enemies) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isAttacking) {
        std::cout << "yo";
        isAttacking = true;
        attackTimer = attackDuration;

        mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        playerPos = sprite.getPosition();
        direction = mousePos - playerPos;

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
                enemy->takeDamage(atk);
            }
        }
    }

    //MOUVEMENTS
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        sprite.move(0, speedY * deltaTime);
        lastSpeedX = 0;
        lastSpeedY = speedY;
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
        lastSpeedX = 0;
        lastSpeedY = -speedY;
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
        lastSpeedX = -speedX;
        lastSpeedY = 0;
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
        lastSpeedX = speedX;
        lastSpeedY = 0;
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
    //JETER UNE BOMBE
    if (bombThrowTimer > bombThrowCooldown && bombCount > 0) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            if (!inventaire.empty()) {
                for (int i = 0; i < inventaire.size(); i++) {
                    if (inventaire[i]->type == "bomb" && throwingOneAtATime == false) {
                        throwingOneAtATime = true;
                        std::shared_ptr<Bomb> bombe = std::make_shared<Bomb>((float)sprite.getPosition().x, (float)sprite.getPosition().y);
                        bombe->speedX = lastSpeedX * 2;
                        bombe->speedY = lastSpeedY * 2;
                        moovingBomb.push_back(bombe);
                        inventaire.erase(inventaire.begin() + i);
                        bombThrowTimer = 0;
                    }
                }
            }
        }
    }
    throwingOneAtATime = false;

    //OUVRIR PORTE
    if (key1) {
        for (int i = 0; i < walls.size(); i++) {
            for (int y = 0; y < walls[i].size(); y++) {
                if (sprite.getGlobalBounds().intersects(walls[i][y]->sprite.getGlobalBounds())) {
                    if (walls[i][y]->lockNumber == "lock1") {
                        walls[i].erase(walls[i].begin() + y);
                        lock1opened = true;
                        for (int j = 0; j < inventaire.size(); j++) {
                            if (inventaire[j]->keyNumber == "key1") inventaire.erase(inventaire.begin() + j);
                        }
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
    checkpointInventaire = inventaire;
}

void Player::checkpointResetPlayer() {
    hp = checkpointHp;
    key1 = checkpointKey1;
    //key1 = false;
    lock1opened = checkpointLock1opened;
    sprite.setPosition(checkpoint);
    potion = false;
    pnjMove = false;
    inventaire = checkpointInventaire;
}
