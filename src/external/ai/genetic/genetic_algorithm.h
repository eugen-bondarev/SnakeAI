#pragma once

#include "../neural_network.h"

class GA 
{
public:
    static NeuralNetwork Crossover(const NeuralNetwork& parent0, const NeuralNetwork& parent1, float mutationRate = 0.02f, float bitMutationRate = 1.0f / 6.5f);
};