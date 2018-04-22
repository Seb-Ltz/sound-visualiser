#pragma once

#include <SFML/Audio.hpp>
#include "StateVisualiser.h"

class StateVisualiser;

class Recorder : public sf::SoundRecorder {
protected:
public:
    Recorder();

    void setState(StateVisualiser *state);

    bool val;
    bool lastVals[19800];
    int valsPtr = 0;

protected:
    bool onProcessSamples(const sf::Int16 *samples, std::size_t sampleCount) override;

    bool onStart() override;

    void onStop() override;

private:
    StateVisualiser *state = nullptr;
};



