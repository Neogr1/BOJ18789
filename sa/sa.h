#ifndef SA_H
#define SA_H

#include "../util.h"

class SimulatedAnnealing {
private:
    const double initialTemperature = 100.0;
    const double coolingRate = 0.99995; // for exponential
    const double coolingSpeed = 0.01; // for linear
    const double minTemperature = 0.5;

    double temperature;

    int calculateMergedScore(int nScore, int cScore);

public:
    int accCount = 0;
    SimulatedAnnealing();
    bool acceptChange(int score, int newScore);
    void updateTemperatureExponential();
    void updateTemperatureLinear();
};

#endif // SA_H