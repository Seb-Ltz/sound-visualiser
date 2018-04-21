//
// Created by sebas on 21/04/2018.
//

#include "Game.h"
#include "StateVisualiser.h"

Game::Game()
    : window(sf::VideoMode(1280, 720), "State Visualiser")
    , state(window)
{
    window.setFramerateLimit(20);

    state.setGame(this);
}

void Game::run() {

    while (window.isOpen())
    {
        state.handleEvents(window);

        state.update();

        window.clear();
        state.render(window);
        window.display();
    }

}
