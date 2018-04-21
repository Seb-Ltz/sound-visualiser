#include <iostream>
#include <SFML/Graphics.hpp>
#include "Recorder.h"
#include "StateVisualiser.h"
#include "Game.h"

sf::RenderWindow window;

int main() {
    Game game;

    game.run();

    return 0;
}