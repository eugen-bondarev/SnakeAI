#pragma once

#include "../neural_network.h"

static value_t BitwiseCrossover(value_t parent0, value_t parent1);
static value_t NumberCrossover(value_t parent0, value_t parent1);
static value_t BitwiseMutation(value_t value);

class GA 
{
public:
    static NeuralNetwork Crossover(const NeuralNetwork& parent0, const NeuralNetwork& parent1, float mutationRate = 0.02f, float bitMutationRate = 1.0f / 6.5f);
};