#include "game.h"

int main() {
    srand(time(NULL));

    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    Game game(modes); 
    game.musicSound.openFromFile("assets/main music.wav");
    game.musicSound.setVolume(10);
    game.musicSound.play();
    game.musicSound.setLoop(true);
    game.run();

    return 0;
}