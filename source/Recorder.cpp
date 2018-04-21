//
// Created by sebas on 21/04/2018.
//

#include <iostream>
#include "Recorder.h"

Recorder::Recorder()
    : SoundRecorder()
{

}

void Recorder::setState(StateVisualiser *state) {
    Recorder::state = state;
}

bool Recorder::onStart() {
    return sf::SoundRecorder::onStart();
}

bool Recorder::onProcessSamples(const sf::Int16 *samples, std::size_t sampleCount) {
    state->setVisualiserData(samples, sampleCount);
    return true;
}

void Recorder::onStop() {
    sf::SoundRecorder::onStop();
}