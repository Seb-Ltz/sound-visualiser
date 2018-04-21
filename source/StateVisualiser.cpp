//
// Created by sebas on 21/04/2018.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include "StateVisualiser.h"
#include "Game.h"
#include "Fourrier.h"
#include <complex>


StateVisualiser::StateVisualiser(sf::RenderWindow &window)
{
    windowSize = window.getSize();

    recorder = new Recorder();
    shape = sf::RectangleShape(sf::Vector2f(100, 100));
    shape.setFillColor(sf::Color::Red);
    recorder->setState(this);
    recorder->start();
}

void StateVisualiser::update() {

}

void StateVisualiser::render(sf::RenderWindow &window) {
    drawVisualiser(window, samples, sampleCount);
}

void StateVisualiser::handleEvents(sf::RenderWindow &window) {
    sf::Event event;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
            window.close();
            recorder->stop();
        }
    }

}

void StateVisualiser::setVisualiserData(const sf::Int16 *samples, std::size_t sampleCount) {
    //Updating the samples array from the Recorder
    StateVisualiser::samples = samples;
    StateVisualiser::sampleCount = sampleCount;
}

void StateVisualiser::drawVisualiser(sf::RenderWindow &window, const sf::Int16 *samples, std::size_t sampleCount) {
    //Nb of points
    int stepsX = 4410;
    //Width of a point
    float shapeSize = (float) windowSize.x / (float) stepsX;

    //Only show half of the graph for more precision
    float resize = 2.0f;

    sf::VertexArray lines(sf::LinesStrip, stepsX);

    if(!showFourrier) {
        for(int i = 0; i < stepsX; i++) {
            int sampleId = (sampleCount / resize / stepsX) * i;

            lines[i].position = sf::Vector2f(i * shapeSize, windowSize.y / 2.0f + (samples[sampleId] / 32767.f) * (windowSize.y / 1.0f));
            lines[i].color = sf::Color::Red;
        }
    } else {

        std::complex<double> X[sampleCount];                // storage for FFT answer
        for(int i = 0; i < sampleCount; i++) {
            X[i] = samples[i] / 100.0f;
        }
        Fourrier::fft2(X, sampleCount);

        for(int i = 0; i < stepsX; i++) {
            int sampleId = (sampleCount / resize / stepsX) * i;

            lines[i].position = sf::Vector2f(i * shapeSize, windowSize.y / 2.0f + (X[sampleId].real() / 32767.f) * (windowSize.y / 4.0f));
            lines[i].color = sf::Color::Red;
        }
    }
    //Draw the graph
    window.draw(lines);
}

void StateVisualiser::setGame(Game *game) {
    StateVisualiser::game = game;
}
