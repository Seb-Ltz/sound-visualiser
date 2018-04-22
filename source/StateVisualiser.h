#pragma once

#include "Recorder.h"
#include <SFML/Graphics.hpp>

class Game;

class Recorder;

class StateVisualiser {

public:
    StateVisualiser(sf::RenderWindow &window);
    void update();
    void render(sf::RenderWindow &window, float dt);
    void handleEvents(sf::RenderWindow &window);

    void setGame(Game *game);

    void setVisualiserData(const sf::Int16 *samples, std::size_t sampleCount);

private:

    void drawVisualiser(sf::RenderWindow &window, const sf::Int16 *samples, std::size_t sampleCount, float dt);
    void handleSoundData(const sf::Int16 *samples, std::size_t sampleCount);
    sf::Vector2u windowSize;
    Recorder* recorder = nullptr;
    sf::RectangleShape shape;
    Game *game;

    std::size_t sampleCount = 0;

    const sf::Int16 *samples;

    const bool showFourrier = false;
    const bool showSoundInput = true;
    const bool showBinary = false;

    //Nb of points
    const int stepsX = 4410;
    const int soundLengthShown = 1; //Change this value if you want to see more on the soundInput graph
    const int soundArrayLen = stepsX * soundLengthShown;
    int soundArrayTimePos = 0;
    int soundArrayWritePos = 0;
    sf::Int16* soundArray;
};



