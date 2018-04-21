//
// Created by sebas on 21/04/2018.
//


#pragma once


#include <SFML/Graphics/RenderWindow.hpp>
#include "StateVisualiser.h"

class Game {

public:
    Game();

    void run();

private:
    sf::RenderWindow window;
    StateVisualiser state;

public:
    sf::RenderWindow* getWindow();

};



