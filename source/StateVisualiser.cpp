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

    soundArray = new sf::Int16[soundArrayLen];
}

void StateVisualiser::update() {

}

void StateVisualiser::render(sf::RenderWindow &window, float dt) {
    drawVisualiser(window, samples, sampleCount, dt);
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

    if(showSoundInput) {
        handleSoundData(samples, sampleCount);
    }
}

void StateVisualiser::drawVisualiser(sf::RenderWindow &window, const sf::Int16 *samples, std::size_t sampleCount, float dt) {

    //Width of a point
    float shapeSize = (float) windowSize.x / (float) stepsX;

    //Only show half of the graph for more precision
    float resize = 2.0f;

    sf::VertexArray lines(sf::LinesStrip, stepsX);

    if(showSoundInput) {
        int soundWritePosId = (soundArrayWritePos) % soundArrayLen;
        soundArrayTimePos = dt * stepsX * 0.1;

        for(int i = 0; i < stepsX; i++) {

            lines[i].position = sf::Vector2f(i * shapeSize, windowSize.y / 2.0f + (soundArray[(soundWritePosId + i * soundLengthShown + soundArrayTimePos) % soundArrayLen] / 32767.f) * (windowSize.y / 2.0f));
            lines[i].color = sf::Color::Red;
        }

        //Draw the graph
        window.draw(lines);
    }
    if (showFourrier) {

        std::complex<double> X[sampleCount];                // storage for FFT answer
        for(int i = 0; i < sampleCount; i++) {
            X[i] = samples[i] / 100.0f;
        }
        Fourrier::fft2(X, sampleCount);

        for(int i = 0; i < stepsX; i++) {
            int sampleId = (sampleCount / resize / stepsX) * i;

            lines[i].position = sf::Vector2f(i * shapeSize, windowSize.y / 2.0f + (X[sampleId].real() / 32767.f) * (windowSize.y / 4.0f));
            lines[i].color = sf::Color::Yellow;
        }

        //Draw the graph
        window.draw(lines);
    }

    if (showBinary)
    {
        sf::RectangleShape rs;
        rs.setSize(sf::Vector2f(10, 10));
        rs.setFillColor(sf::Color::Red);

        window.draw(rs);
        if (recorder->val)
            rs.setFillColor(sf::Color::Green);
        rs.setPosition(0, 10);
        window.draw(rs);
        rs.setSize(sf::Vector2f(1, 10));
        for (int i = 0; i < 19800; i++)
        {
            rs.setFillColor(sf::Color::Red);
            if (recorder->lastVals[i])
                rs.setFillColor(sf::Color::Green);
            if (i == recorder -> valsPtr)
                rs.setFillColor(sf::Color::Blue);
            rs.setPosition(i % 1980, i / 1980 * 10);
            window.draw(rs);
        }
    }

}

void StateVisualiser::setGame(Game *game) {
    StateVisualiser::game = game;
}

void StateVisualiser::handleSoundData(const sf::Int16 *samples, std::size_t sampleCount) {

    for(int i = 0; i < stepsX; i++) {
        int sampleId = (sampleCount / stepsX) * i;
        soundArrayWritePos++;

        //Add the new samples to the circular array
        soundArray[(soundArrayWritePos) % soundArrayLen] = samples[sampleId];

    }
}