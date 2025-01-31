#include "game.h"
#include "menu.h"

Game::Game() : window(sf::VideoMode(1200, 800), "Escape the Dungeon"), player(75, 75) {
}

void Game::showMenu() {
    Menu menu(window.getSize().x, window.getSize().y);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up)
                    menu.moveUp();
                if (event.key.code == sf::Keyboard::Down)
                    menu.moveDown();
                if (event.key.code == sf::Keyboard::Enter) {
                    int selection = menu.getSelectedIndex();
                    if (selection == 0) return;
                    if (selection == 1) std::cout << "Options sélectionnées" << std::endl;
                    if (selection == 2) window.close();
                }
            }

            if (event.type == sf::Event::MouseMoved) {
                menu.handleMouseHover(window);
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    int selection = menu.handleMouseClick(window);
                    if (selection == 0) return;
                    if (selection == 1) std::cout << "Options sélectionnées" << std::endl;
                    if (selection == 2) window.close();
                }
            }
        }

        window.clear();
        menu.draw(window);
        window.display();
    }
}

void Game::gameLoop() {
    while (window.isOpen()) {
        deltaTime = Clock.restart().asSeconds();
        updateAll();
        pollEvent();
        drawAll();
    }
}

void Game::pollEvent() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                /*if (gameOver) */window.close();
            }
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (gameOver || win) {
                    if (retryText.getGlobalBounds().contains((float)event.mouseButton.x, (float)event.mouseButton.y)) {
                        reset();
                        win = false;
                        gameOver = false;
                        playing = true;
                    }
                    else if (menuText.getGlobalBounds().contains((float)event.mouseButton.x, (float)event.mouseButton.y)) {
                        win = false;
                        gameOver = false;
                        showMenu();  // Retourner au menu principal
                    }
                }
            }
        }
        if (event.type == sf::Event::MouseMoved) {
            if (gameOver || win) {
                if (retryText.getGlobalBounds().contains((float)event.mouseMove.x, (float)event.mouseMove.y)) {
                    retryText.setFillColor(sf::Color::Yellow);
                }
                else {
                    retryText.setFillColor(sf::Color::White);
                }

                if (menuText.getGlobalBounds().contains((float)event.mouseMove.x, (float)event.mouseMove.y)) {
                    menuText.setFillColor(sf::Color::Yellow);
                }
                else {
                    menuText.setFillColor(sf::Color::White);
                }
            }
        }
    }
}

void Game::updateAll() {
    if (playing) {
        //std::cout << player.speedX << " - " << player.speedY << "               " << player.potionTimer << std::endl;
        player.update(deltaTime);
        player.handleInput(deltaTime, window, wallSprite, theMap.mapObjects);
        player.potionTimer += deltaTime;
        player.potionUpdate(deltaTime);

        //COLLISIONS
        /*if (!enemies.empty()) {
            for (auto& enemy : enemies) {
                enemy->update(deltaTime);
                enemy->behavior(deltaTime, wallSprite, theMap.mapObjects, player);
                if (player.sprite.getGlobalBounds().intersects(enemy->sprite.getGlobalBounds())) {
                    playing = false;
                    gameOver = true;
                }
            }
        }*/
        if (!theMap.enemies.empty()) {
            for (auto& enemyz : theMap.enemies) {
                for (auto& enemy : enemyz) {
                    enemy->update(deltaTime);
                    enemy->behavior(deltaTime, wallSprite, theMap.mapObjects, player);
                    if (player.sprite.getGlobalBounds().intersects(enemy->sprite.getGlobalBounds())) {
                        playing = false;
                        gameOver = true;
                    }
                }
            }
        }
        /*if (!objects.empty()) {
            for (auto& obj : objects) {
                if (player.sprite.getGlobalBounds().intersects(obj->sprite.getGlobalBounds())) {
                    obj->interact(player, theMap.objects);
                }
            }
        }*/
        if (!theMap.objects.empty()) {
            for (auto& objz : theMap.objects) {
                for (auto& obj : objz) {
                    if (player.sprite.getGlobalBounds().intersects(obj->sprite.getGlobalBounds())) {
                        obj->interact(player, theMap.objects);
                    }
                }
            }
        }
       /* for (int i = 0; i < objects.size(); i++) {
            if (objects[i]->state == false) {
                objects.erase(objects.begin() + i);
            }
        }
        for (int i = 0; i < theMap.objects.size(); i++) {
            if (!theMap.objects[i].empty()) {
                for (int y = 0; y < theMap.objects[i].size(); i++) {
                    if (theMap.objects[i][y]->state == false) {
                        theMap.objects[i].erase(theMap.objects[i].begin() + y);
                    }
                }
            }
        }*/
        /*for (auto& wallz : theMap.mapObjects) {
            for (auto& wall : wallz) {
                wallSprite.setPosition(wall->sprite.getPosition());
            }
        }*/

        if (player.sprite.getPosition().x > window.getSize().x || player.sprite.getPosition().y > window.getSize().y
            || player.sprite.getPosition().x < 0 || player.sprite.getPosition().y < 0) {
            win = true;
            playing = false;
        }
    }
}

void Game::drawAll() {
    window.clear();
    if (playing) {
        if (!theMap.mapObjects.empty()) {
            for (auto& objz : theMap.mapObjects) {
                for (auto& obj : objz) {
                    /*if (obj->type == "wall") {
                        wallSprite.setScale(obj->sprite.getScale());
                        wallSprite.setPosition(obj->sprite.getPosition());
                        window.draw(wallSprite);
                    }
                    else if (obj->type == "floor") {
                        floorSprite.setScale(obj->sprite.getScale());
                        floorSprite.setPosition(obj->sprite.getPosition());
                        window.draw(floorSprite);
                    }*/
                    if (obj->type == "wall") {
                        obj->sprite.setTexture(wallTexture);
                    }
                    else if (obj->type == "floor") obj->sprite.setTexture(floorTexture);
                    else if (obj->type == "lock") obj->sprite.setTexture(lockTexture);
                    window.draw(obj->sprite);
                }
            }
        }
        player.sprite.setTexture(playerTexture);
        keyIcone.setTexture(keyTexture);
        if (player.key) window.draw(keyIcone);
        player.draw(window);
        /*if (!enemies.empty()) {
            for (auto& enemy : enemies) {
                if (enemy->type == "chaser") enemy->sprite.setTexture(chaserTexture);
                else if (enemy->type == "patrolling") enemy->sprite.setTexture(patrollingTexture);
                enemy->draw(window);
            }
        }*/
        if (!theMap.enemies.empty()) {
            for (auto& enemyz : theMap.enemies) {
                for (auto& enemy : enemyz) {
                    if (enemy->type == "chaser") enemy->sprite.setTexture(chaserTexture);
                    else if (enemy->type == "patrolling") enemy->sprite.setTexture(patrollingTexture);
                    enemy->draw(window);
                }
            }
        }
        /*if (!objects.empty()) {
            for (auto& obj : objects) {
                if (obj->type == "potion") obj->sprite.setTexture(potionTexture);
                else if (obj->type == "key") obj->sprite.setTexture(keyTexture);
                window.draw(obj->sprite);
            }
        }*/
        if (!theMap.objects.empty()) {
            for (auto& objz : theMap.objects) {
                for (auto& obj : objz) {
                    if (obj->type == "potion") obj->sprite.setTexture(potionTexture);
                    else if (obj->type == "key") obj->sprite.setTexture(keyTexture);
                    window.draw(obj->sprite);
                }
            }
        }
    }
    if (win) {
        window.draw(winText);
        window.draw(retryText);
        window.draw(menuText);
    }
    if (gameOver) {
        window.draw(gameOverText);
        window.draw(retryText);
        window.draw(menuText);
    }
    window.display();
}

void Game::loadTextures() {
    theMap.loadMap();
    playerTexture.loadFromFile("assets/player.png");
    chaserTexture.loadFromFile("assets/chaser.png");
    patrollingTexture.loadFromFile("assets/patrolling.png");
    potionTexture.loadFromFile("assets/potion.png");
    keyTexture.loadFromFile("assets/key.png");
    wallTexture.loadFromFile("assets/wall.png");
    floorTexture.loadFromFile("assets/floor.png");
    lockTexture.loadFromFile("assets/lock.png");

    baseFont.loadFromFile("assets/Arial.ttf");

    winText.setFont(baseFont);
    winText.setString("WIN");
    winText.setCharacterSize(100);
    winText.setPosition((window.getSize().x - winText.getGlobalBounds().width) / 2,
        (window.getSize().y - winText.getCharacterSize()) / 3);
    winText.setFillColor(sf::Color::Yellow);

    gameOverText.setFont(baseFont);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(100);
    gameOverText.setPosition((window.getSize().x - gameOverText.getGlobalBounds().width) / 2,
        (window.getSize().y - gameOverText.getCharacterSize()) / 3);
    gameOverText.setFillColor(sf::Color::Red);

    retryText.setFont(baseFont);
    retryText.setString("RETRY ?");
    retryText.setCharacterSize(50);
    retryText.setPosition((window.getSize().x - retryText.getGlobalBounds().width) / 2,
        gameOverText.getPosition().y + gameOverText.getCharacterSize() + window.getSize().y * 0.1);
    retryText.setFillColor(sf::Color::White);

    menuText.setFont(baseFont);
    menuText.setString("MENU");
    menuText.setCharacterSize(50);
    menuText.setPosition(
        (window.getSize().x - menuText.getGlobalBounds().width) / 2,
        retryText.getPosition().y + retryText.getCharacterSize() + 20
    );
    menuText.setFillColor(sf::Color::White);

    keyIcone.setTexture(keyTexture);
    keyIcone.setScale(0.075, 0.075);
    keyIcone.setPosition(0, 0);
    wallSprite.setTexture(wallTexture);
    floorSprite.setTexture(floorTexture);
    lockSprite.setTexture(lockTexture);
}

void Game::setupSpawns() {
    //std::unique_ptr<Enemy> chaser = std::make_unique<ChaserEnemy>(100, 100);
    //enemies.push_back(chaser);
    enemies.emplace_back(std::make_unique<ChaserEnemy>(700, 700));
    //std::unique_ptr<PatrollingEnemy> patrolling = std::make_unique<PatrollingEnemy>(700, 700);
    //patrollings.push_back(patrolling);
    enemies.emplace_back(std::make_unique<PatrollingEnemy>(500, 500));
    enemies.emplace_back(std::make_unique<PatrollingEnemy>(300, 300));
    enemies.emplace_back(std::make_unique<PatrollingEnemy>(900, 200));

    objects.emplace_back(std::make_unique<Potion>());
    objects.emplace_back(std::make_unique<Key>());
    for (auto& obj : objects) {
        obj->sprite.setPosition(rand() % window.getSize().x * 0.9, rand() % window.getSize().y * 0.9);
    }
}

void Game::reset() {
    enemies.clear();
    theMap.enemies.clear();
    objects.clear();
    theMap.objects.clear();
    theMap.mapObjects.clear();
    player.sprite.setPosition(75, 75);
    player.potion = false;
    player.key = false;
    //setupSpawns();
    theMap.loadMap();
}

void Game::run() {
    showMenu();
    loadTextures();
    //setupSpawns();
    gameLoop();
}