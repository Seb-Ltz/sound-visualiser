//
// Created by sebas on 21/04/2018.
//

#include "Game.h"
#include "StateVisualiser.h"

Game::Game()
    : window(sf::VideoMode(1280, 720), "State Visualiser")
    , state(window)
{
    window.setFramerateLimit(60);

    state.setGame(this);
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();
        state.handleEvents(window);

        state.update();

        window.clear();
        state.render(window, dt);
        window.display();
    }

}
