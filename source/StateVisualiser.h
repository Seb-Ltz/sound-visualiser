#pragma once

#include "Recorder.h"
#include <SFML/Graphics.hpp>

class Game;

class Recorder;

class StateVisualiser {

public:
    StateVisualiser(sf::RenderWindow &window);
    void update();
    void render(sf::RenderWindow &window);
    void handleEvents(sf::RenderWindow &window);

    void setGame(Game *game);

    void setVisualiserData(const sf::Int16 *samples, std::size_t sampleCount);

private:

    void drawVisualiser(sf::RenderWindow &window, const sf::Int16 *samples, std::size_t sampleCount);

    sf::Vector2u windowSize;
    Recorder* recorder = nullptr;
    sf::RectangleShape shape;
    Game *game;

    std::size_t sampleCount = 0;

    const sf::Int16 *samples;

    bool showFourrier = false;
};



