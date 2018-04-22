//
// Created by sebas on 21/04/2018.
//

#include <iostream>
#include "Recorder.h"
#include <math.h>

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
    int s = 0;
    val = false;
    for (int i = 0; i < sampleCount; i++)
    {
        if (abs(samples[i]) > 100)
        {
            val = true;
        }
        s++;
        if (s = 150 || s == sampleCount - 1)
        {
            s = 0;
            lastVals[valsPtr] = val;
            valsPtr++;
            if (valsPtr == 19800)
                valsPtr = 0;
            val = false;
        }
    }

    return true;
}

void Recorder::onStop() {
    sf::SoundRecorder::onStop();
}
