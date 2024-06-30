#include <cstdlib>
#include <cmath>
#include "sa.h"

SimulatedAnnealing::SimulatedAnnealing() {
    temperature = initialTemperature;
}

bool SimulatedAnnealing::acceptChange(int score, int newScore) {
    if (newScore > score) {
        updateTemperatureExponential();
        accCount++;
        return true;
    } else {
        double probability = exp((newScore - score) / temperature);
        double randomValue = static_cast<double>(rand()) / RAND_MAX;

        updateTemperatureExponential();
        accCount += randomValue < probability;
        return randomValue < probability;
    }
}

void SimulatedAnnealing::updateTemperatureExponential() {
    temperature *= coolingRate;
    if (temperature < minTemperature)
        temperature = minTemperature;
}

void SimulatedAnnealing::updateTemperatureLinear() {
    temperature -= coolingSpeed;
    if (temperature < minTemperature)
        temperature = minTemperature;
}

